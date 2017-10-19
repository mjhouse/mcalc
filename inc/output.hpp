#ifndef MCALC_OUTPUT_HPP
#define MCALC_OUTPUT_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Event;

	class Output : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::Label* widget;
			std::function<double(std::vector<mc::Interface*>)> calculator;

		public:
			Output( Gtk::Label* w, json* d);
			~Output();

			void notify(Event* e);
			void broadcast();

			void set_references( std::vector<Interface*> r );
			void set_calculator( std::function<double(std::vector<mc::Interface*>)> f );
			std::string get_value();
			void set_value( double v );
	};

}

#endif
