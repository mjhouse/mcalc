#include "output.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	Output::Output( Gtk::Label* w, json* d){
		widget = w;
		data = d;
	};

	Output::~Output(){};

	void Output::notify( Event* e ){
		if(_in(e->sender(),references)){
			double result = calculator(references);
			set_value(result);
		}
	};

	void Output::broadcast(){
		broadcaster->broadcast(new Event(this));
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
