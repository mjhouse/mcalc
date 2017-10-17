#include "mclib.hpp"

namespace mc {

	Broadcaster* Broadcaster::get_instance() {
		static Broadcaster instance;
		return &instance;
	}

	void Broadcaster::subscribe(Subscriber* s) {
		subscribers.push_back(s);
	}

	void Broadcaster::broadcast( Subscriber* s ) {
		for(auto& a : subscribers){
			a->notify(s);
		}
	}

	ComboBoxText::ComboBoxText( Gtk::ComboBoxText* w, json* d, std::string n ){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);
		widget = w;
		data = d;
		name = n;

		w->signal_changed().connect(sigc::mem_fun(*this,
			&ComboBoxText::broadcast));
	};
	ComboBoxText::~ComboBoxText(){};

	void ComboBoxText::broadcast(){
		broadcaster->broadcast(this);
	}

	void ComboBoxText::notify( Subscriber* s ){
		if(s != this) {
			if(!references.empty()){
				std::vector<std::string> v;
				for(auto& a : references){
					v.push_back(a->get_value());
				}
				this->set_value(v);
			}
		}
	};

	void ComboBoxText::set_references( std::vector<Interface*> i ){ references = i; };

	std::string ComboBoxText::get_value(){
		return widget->get_active_text();
	};

	void ComboBoxText::set_value( std::vector<std::string> v ){
		gtk_combo_box_text_remove_all(widget->gobj());
		json d = *data;

		for(auto& str : v){ d = d[str]; }

		for(json::iterator it = d.begin(); it != d.end(); ++it){
			widget->append(it.key());
			/*
			if (!(*it).is_primitive()) {
				widget->append(it.key());
			} else {
				if (it->type() != json::value_t::null){
					widget->append(it->get<std::string>());
				}
			}
			*/
		}
	};

	/* ---------------------------------------------------------------------- */

	void set_slider( Gtk::Scale* s, sigc::connection h, json j ) {
		if (j.is_array()) {
			std::vector<double> v;
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				std::string val = it->get<std::string>();
				v.push_back(std::stod(val));
			}
			double min = *std::min_element(v.begin(),v.end());
			double max = *std::max_element(v.begin(),v.end());
			double mid = (max-min)/2+min;
			s->set_range(min,max);
			s->set_value(mid);
			s->clear_marks();
			s->add_mark(mid,Gtk::POS_BOTTOM,"default");
		}
	}

	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d ){
		if(d.type() != json::value_t::null){
			h.block(true);
			gtk_combo_box_text_remove_all(c->gobj());
			for (json::iterator it = d.begin(); it != d.end(); ++it) {
				json j = *it;
				if (!j.is_primitive()) {
					c->append(it.key());
				} else {
					if (it->type() != json::value_t::null){
						c->append(it->get<std::string>());
					}
				}
			}
			h.block(false);
			c->set_active(0);
		}
	}

	double calculate_rpm ( double v, double d ) {
		double rpm = (4.0*v)/d;
		if(!std::isinf(rpm)){
			return rpm;
		} else {
			return 0.0;
		}
	};

}
