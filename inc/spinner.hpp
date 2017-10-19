#ifndef MCALC_SPINNER_HPP
#define MCALC_SPINNER_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Event;

	class Spinner : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::SpinButton* widget;

		public:
			Spinner( Gtk::SpinButton* w, json* d);
			~Spinner();

			void notify(Event* e);
			void broadcast();

			void set_references( std::vector<Interface*> r );
			std::string get_value();
			void set_value( double d );
	};
}

#endif
