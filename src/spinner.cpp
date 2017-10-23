#include "spinner.hpp"
#include "broadcaster.hpp"

namespace mc {

	Spinner::Spinner(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::SpinButton(cobject),
	 	blocked (false) {
	};

	Spinner::~Spinner(){
		references.clear();
	};

	void Spinner::notify(Event* e){
		switch(e->type()){
			case Event::Type::SINGLE:
				break;
			case Event::Type::ALL:
				break;
		}
	};

	/* Broadcast when the value changes */
	void Spinner::on_value_changed(){
		// if block flag isn't set, broadcast
		if(!blocked){
			broadcaster->broadcast(Event(this));
			Gtk::SpinButton::on_value_changed();
		}
	}

	void Spinner::set_references( std::vector<mc::Interface*> r ){
		references = r;
	};

	std::string Spinner::get_value(){
		return std::to_string(Gtk::SpinButton::get_value());
	};

	void Spinner::set_value( double d ){
		this->set_value(d);
	};
}
