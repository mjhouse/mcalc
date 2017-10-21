#include "output.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

namespace mc {

	Output::Output(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::Label(cobject) {
	};

	Output::~Output(){
		references.clear();
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

	void Output::set_data(json* d){
		data = d;
	}

	void Output::broadcast(){
		broadcaster->broadcast(Event(this));
	};

	void Output::set_references( std::vector<mc::Interface*> r ){
		references = r;
	};

	void Output::set_calculator( std::function<double(std::vector<mc::Interface*>)> f ){
		calculator = f;
	};

	std::string Output::get_value(){
		return this->get_text();
	};

	void Output::set_value( double v ){
		this->set_text(std::to_string(v));
	};

}
