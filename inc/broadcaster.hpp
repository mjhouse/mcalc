#ifndef MCALC_BROADCASTER_HPP
#define MCALC_BROADCASTER_HPP

#include <vector>

namespace mc {

	class Interface;

	class Broadcaster {
		private:
			std::vector<Interface*> subscribers;
			Broadcaster() : subscribers({}) {};

		public:
			static Broadcaster* get_instance();
			void subscribe(Interface* s);
			void broadcast(Interface* s);
	};

}

#endif
