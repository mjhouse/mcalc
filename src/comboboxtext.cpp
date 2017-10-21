#include "comboboxtext.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	/* -------------------------------------------------------------------------
		ComboBoxText */
	ComboBoxText::ComboBoxText(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::ComboBoxText(cobject),
	 	blocked (false) {
	};

	/* The destructor */
	ComboBoxText::~ComboBoxText(){
		references.clear();
	};

	/* Broadcast when the value changes */
	void ComboBoxText::on_changed(){
		// if block flag isn't set, broadcast
		if(!blocked){
			broadcaster->broadcast(Event(this));
			Gtk::ComboBoxText::on_changed();
		}
	}

	/* Receive events when other widgets change */
	void ComboBoxText::notify( Event* e ){
		switch(e->type()){
			case Event::Type::SINGLE:
				if(_in(e->sender(),references)) {
					populate();
				}
				break;
			case Event::Type::ALL:
				break;
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

	void ComboBoxText::set_data(json* d){
		data = d;
	}

	void ComboBoxText::set_references( std::vector<mc::Interface*> i ){
		references = i;
		populate();
	};

	std::string ComboBoxText::get_value(){
		return this->get_active_text();
	};

	void ComboBoxText::block( bool b ){
		blocked = b;
	}

	void ComboBoxText::set_value( std::vector<std::string> v ){
		this->block(true);
		gtk_combo_box_text_remove_all(this->gobj());
		json d = *data;

		for(auto& str : v){ d = d[str]; }
		for(json::iterator it = d.begin(); it != d.end(); ++it){
			if (!(*it).is_primitive()) {
				this->append(it.key());
			} else {
				if (it->type() != json::value_t::null){
					this->append(it->get<std::string>());
				}
			}
		}
		this->set_active(0);
		this->block(false);
	};

}
