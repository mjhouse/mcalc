#include "mclib.hpp"

namespace mc {

	Broadcaster* Broadcaster::get_instance() {
		static Broadcaster instance;
		return &instance;
	}

	void Broadcaster::subscribe(Subscriber* s) {
		subscribers.push_back(s);
	}

	void Broadcaster::broadcast( Interface* s ) {
		for(auto& a : subscribers){
			a->notify(s);
		}
	}

	/* -------------------------------------------------------------------------
		ComboBoxText */
	ComboBoxText::ComboBoxText( Gtk::ComboBoxText* w, json* d){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);
		widget = w;
		data = d;

		on_change_conn = w->signal_changed().connect(sigc::mem_fun(*this,
			&ComboBoxText::broadcast));
	};

	ComboBoxText::~ComboBoxText(){};

	void ComboBoxText::broadcast(){
		broadcaster->broadcast(this);
	}

	void ComboBoxText::notify( Interface* s ){
		if(_IN(s,references)) {
			populate();
		}
	};

	void ComboBoxText::populate(){
		if(!references.empty()){
			std::vector<std::string> v;
			for(auto& a : references){
				v.push_back(a->get_value());
			}
			this->set_value(v);
		}
	};

	void ComboBoxText::set_references( std::vector<Interface*> i ){
		references = i;
		populate();
	};

	std::string ComboBoxText::get_value(){
		return widget->get_active_text();
	};

	void ComboBoxText::set_value( std::vector<std::string> v ){
		on_change_conn.block(true);
		gtk_combo_box_text_remove_all(widget->gobj());
		json d = *data;

		for(auto& str : v){ d = d[str]; }
		for(json::iterator it = d.begin(); it != d.end(); ++it){
			if (!(*it).is_primitive()) {
				widget->append(it.key());
			} else {
				if (it->type() != json::value_t::null){
					widget->append(it->get<std::string>());
				}
			}
		}
		widget->set_active(0);
		on_change_conn.block(false);
	};
	/* ---------------------------------------------------------------------- */

	/* -------------------------------------------------------------------------
		Slider */
	Slider::Slider( Gtk::Scale* w, json* d){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);
		widget = w;
		data = d;

		on_change_conn = w->signal_value_changed().connect(sigc::mem_fun(*this,
			&Slider::broadcast));
	};

	Slider::~Slider(){};

	void Slider::broadcast(){
		broadcaster->broadcast(this);
	}

	void Slider::notify( Interface* s ){
		if(_IN(s,start_ref)||_IN(s,end_ref)){
			populate();
		}
	};

	void Slider::set_references( std::vector<Interface*> s, std::vector<Interface*> e ){
		start_ref = s;
		end_ref = e;
		populate();
	};

	void Slider::populate(){
		/*
		json d = *data;

		for(auto& a : references){d = d[a->get_value()];}

		std::vector<double> hard_values;
		std::vector<double> tough_values;

		json hard = d["hard"];
		json tough = d["tough"];
		for(auto& b : hard["speed"]){
			std::string val = b.get<std::string>();
			hard_values.push_back(std::stod(val));
		}

		for(auto& b : tough["speed"]){
			std::string val = b.get<std::string>();
			tough_values.push_back(std::stod(val));
		}

		double h_max = *std::max_element(hard_values.begin(),hard_values.end());
		double h_min = *std::min_element(hard_values.begin(),hard_values.end());
		double t_max = *std::max_element(tough_values.begin(),tough_values.end());
		double t_min = *std::min_element(tough_values.begin(),tough_values.end());
		*/
	};

	std::string Slider::get_value(){
		return std::to_string(widget->get_value());
	};

	void Slider::set_value( double max, double min, double val ){
		on_change_conn.block(true);

		on_change_conn.block(false);
	};
	/* ---------------------------------------------------------------------- */



















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
