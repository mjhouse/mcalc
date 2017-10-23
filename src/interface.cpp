#include "interface.hpp"
#include "broadcaster.hpp"
#include "datastore.hpp"

namespace mc {

	Interface::Interface(){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);

		data = DataStore::get_instance();
	};

	Interface::~Interface(){};

}
