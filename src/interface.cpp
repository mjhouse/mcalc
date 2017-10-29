#include "interface.hpp"
#include "broadcaster.hpp"
#include "datastore.hpp"

namespace mc {

	Interface::Interface()
	:	broadcaster(Broadcaster::get_instance()),
		data(DataStore::get_instance())
	{
		broadcaster->subscribe(this);
	}

	Interface::~Interface(){}

	void Interface::set_column( std::string n ){
		column_name = n;
	}

	std::string Interface::get_column(){
		return column_name;
	}

	/* -------------------------------------------------------------------------
	 	DummyInterface */

	DummyInterface::DummyInterface( std::string s ){
		value = s;
	}

	std::string DummyInterface::get_value(){
		return value;
	}

	void DummyInterface::set_value( std::string s ){
		value = s;
	}

	void DummyInterface::set_column( std::string n ){
		column_name = n;
	}

	std::string DummyInterface::get_column(){
		return column_name;
	}

	void DummyInterface::notify(Event* /* e */){

	}

	void DummyInterface::broadcast(){

	}

}
