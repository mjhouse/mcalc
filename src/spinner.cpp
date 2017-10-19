#include "spinner.hpp"
#include "broadcaster.hpp"

namespace mc {

	Spinner::Spinner( Gtk::SpinButton* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_value_changed().connect(sigc::mem_fun(*this,
			&Spinner::broadcast));
	};

	Spinner::~Spinner(){};

	void Spinner::notify(Event* e){
		switch(e->type()){
			case Event::Type::SINGLE:
				break;
			case Event::Type::ALL:
				break;
		}
	};

	void Spinner::broadcast(){
		broadcaster->broadcast(new Event(this));
	};

	void Spinner::set_references( std::vector<Interface*> r ){
		references = r;
	};

	std::string Spinner::get_value(){
		return std::to_string(widget->get_value());
	};

	void Spinner::set_value( double d ){
		widget->set_value(d);
	};
}
