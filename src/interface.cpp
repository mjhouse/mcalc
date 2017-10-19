#include "interface.hpp"
#include "broadcaster.hpp"

namespace mc {

	Interface::Interface(){
		broadcaster = Broadcaster::get_instance();
		broadcaster->subscribe(this);
	};

	Interface::~Interface(){};

}
