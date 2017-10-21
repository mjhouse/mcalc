#include "output.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	Output::Output( Gtk::Label* w, json* d){
		widget = w;
		data = d;
	};

	Output::~Output(){
		references.clear();
		delete widget;
		widget = nullptr;
	};

	void Output::notify( Event* e ){
		switch(e->type()){
			case Event::Type::SINGLE:
				if(_in(e->sender(),references)){
					double result = calculator(references);
					set_value(result);
				}
				break;
			case Event::Type::ALL:
				if(e->sender()!=this){
					double result = calculator(references);
					set_value(result);
				}
				break;
		}
	};

	void Output::broadcast(){
		broadcaster->broadcast(Event(this));
	};

	void Output::set_references( std::vector<Interface*> r ){
		references = r;
	};

	void Output::set_calculator( std::function<double(std::vector<mc::Interface*>)> f ){
		calculator = f;
	};

	std::string Output::get_value(){
		return widget->get_text();
	};

	void Output::set_value( double v ){
		widget->set_text(std::to_string(v));
	};

}
