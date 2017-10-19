#ifndef MCALC_SLIDER_HPP
#define MCALC_SLIDER_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Interface;
	class Event;

	class Slider : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> start_ref;
			std::vector<Interface*> end_ref;
			Gtk::Scale* widget;
			Interface* scaler;
			std::map<double,std::string> marks;

		public:
			Slider( Gtk::Scale* w, json* d);
			~Slider();

			void notify(Event* e);
			void broadcast();
			void populate();


			void set_marks();
			void set_marks( std::map<double,std::string> m );
			void set_scaler( Interface* i );
			void set_references( std::vector<Interface*> s, std::vector<Interface*> e );
			std::string get_value();
			void set_value( double max, double min, double val );
	};

}

#endif
