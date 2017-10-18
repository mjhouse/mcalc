#include "broadcaster.hpp"
#include "interface.hpp"

namespace mc {
	Broadcaster* Broadcaster::get_instance() {
		static Broadcaster instance;
		return &instance;
	}

	void Broadcaster::subscribe(Interface* s) {
		subscribers.push_back(s);
	}

	void Broadcaster::broadcast( Interface* s ) {
		for(auto& a : subscribers){
			a->notify(s);
		}
	}
}
