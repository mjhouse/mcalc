#include "comboboxtext.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	/* -------------------------------------------------------------------------
		ComboBoxText */
	ComboBoxText::ComboBoxText( Gtk::ComboBoxText* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_changed().connect(sigc::mem_fun(*this,
			&ComboBoxText::broadcast));
	};

	ComboBoxText::~ComboBoxText(){};

	void ComboBoxText::notify( Event* e ){
		if(_in(e->sender(),references)) {
			populate();
		}
	};

	void ComboBoxText::broadcast(){
		broadcaster->broadcast(this);
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

}
