#ifndef MCALC_COMBOBOXTEXT_HPP
#define MCALC_COMBOBOXTEXT_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Interface;
	class Event;

	class ComboBoxText : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::ComboBoxText* widget;

		public:
			ComboBoxText( Gtk::ComboBoxText* w, json* d);
			~ComboBoxText();

			void notify(Event* e);
			void broadcast();
			void populate();

			void set_references( std::vector<Interface*> i );
			std::string get_value();
			void set_value( std::vector<std::string> v );
	};

}

#endif
