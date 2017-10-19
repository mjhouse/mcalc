#ifndef MCALC_BROADCASTER_HPP
#define MCALC_BROADCASTER_HPP

#include <vector>

namespace mc {

	class Interface;
	class Event;

	class Broadcaster {
		private:
			std::vector<Interface*> subscribers;
			Broadcaster() : subscribers({}) {};

		public:
			static Broadcaster* get_instance();
			void subscribe(Interface* s);
			void broadcast(Event e);
	};

	class Event {

		enum Type { ALL, SINGLE };

		private:
			Event::Type	event_type;
			Interface*	event_sender;

		public:
			Event( Type t, Interface* s );
			~Event(){};

			Event::Type type();
			Interface* sender();
	};

}

#endif
