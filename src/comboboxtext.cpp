#include "datastore.hpp"
#include "comboboxtext.hpp"
#include "broadcaster.hpp"
#include <set>

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	/* -------------------------------------------------------------------------
		ComboBoxText */
	ComboBoxText::ComboBoxText(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::ComboBoxText(cobject),
		blocked (false),
		glade_ref(refGlade)
	{

	}

	/* The destructor */
	ComboBoxText::~ComboBoxText(){
		references.clear();
	}

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
	}

	void ComboBoxText::populate(){
		if(!references.empty()){
			this->set_value(references);
		}
	}

	void ComboBoxText::set_references( std::vector<mc::Interface*> i ){
		references = i;
		populate();
	}

	std::string ComboBoxText::get_value(){
		return this->get_active_text();
	}

	void ComboBoxText::block( bool b ){
		blocked = b;
	}

	void ComboBoxText::set_value( std::vector<mc::Interface*> v ){
		this->block(true);

		// clear the contents of the comboboxtext ui
		gtk_combo_box_text_remove_all(this->gobj());

		// get a vector<vector<string>> set of records from the database
		Records r = data->get(v,std::vector<std::string>{this->get_column()});

		// get a unique collection of column values
		// and append it to this comboboxtext
		std::set<std::string> values;
		for (auto& a : r){ values.insert(a[0]); }
		for (auto& b : values){ this->append(b); }

		this->set_active(0);
		this->block(false);
	}

}
