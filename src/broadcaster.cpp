#include "broadcaster.hpp"
#include "interface.hpp"

namespace mc {

	/* -------------------------------------------------------------------------
	 	Broadcaster*/
	Broadcaster* Broadcaster::get_instance() {
		static Broadcaster instance;
		return &instance;
	}

	Broadcaster::~Broadcaster() {}

	void Broadcaster::subscribe(Interface* s) {
		interfaces.push_back(s);
	}

	void Broadcaster::subscribe(Subscriber* s) {
		subscribers.push_back(s);
	}

	void Broadcaster::broadcast( Event e ) {
		for(auto& a : interfaces){
			a->notify(&e);
		}
		for(auto& a : subscribers){
			a->notify(&e);
		}
	}

	/* -------------------------------------------------------------------------
	 	Broadcast Event */

	Event::Event( Type t){
		event_type = t;
		event_sender = nullptr;
	};

	Event::Event( Interface* s ){
		event_type = Event::Type::SINGLE;
		event_sender = s;
	};

	Event::Event( Type t, Interface* s ){
		event_type = t;
		event_sender = s;
	};

	Event::Type Event::type(){
		return event_type;
	};

	Interface* Event::sender(){
		return event_sender;
	};

}
