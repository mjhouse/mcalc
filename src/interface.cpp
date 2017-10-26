#include "interface.hpp"
#include "broadcaster.hpp"
#include "datastore.hpp"

namespace mc {

	Interface::Interface(){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);

		column_name = "NONE";
		data = DataStore::get_instance();
	};

	Interface::~Interface(){};

	void Interface::set_column( std::string n ){
		column_name = n;
	};

	std::string Interface::get_column(){
		return column_name;
	};


}
