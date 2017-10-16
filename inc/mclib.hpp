#ifndef MCALC_MCLIB_HPP
#define MCALC_MCLIB_HPP

#include <vector>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Interface;

	class Broadcast {
		private:
			Broadcast();
		public:
			~Broadcast();

		private:
			std::vector<Interface> subscribers;

		public:

			enum Type {
				test,
			};

			static Broadcast* get() {
				static Broadcast instance;
				return &instance;
			}

			void subscribe( Interface i );
			void unsubscribe( Interface i );
			void broadcast( Type t );
	};

	class Interface {
		private:
			sigc::connection	connection;
			Gtk::Widget*		widget;

		public:
			Interface();
			~Interface();
			void update( json d );
			void notify( Broadcast::Type t );
	};


	void set_slider( Gtk::Scale* s, sigc::connection h, json j );
	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d );
	double calculate_rpm ( double v, double d );
}

#endif
