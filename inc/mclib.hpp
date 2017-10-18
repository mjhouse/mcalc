#ifndef MCALC_MCLIB_HPP
#define MCALC_MCLIB_HPP

#include <vector>
#include <iostream>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json;

#define _IN(E,V) (std::find(V.begin(), V.end(), E) != V.end())

#define _max(V) (*std::max_element(V.begin(),V.end()))
#define _min(V) (*std::min_element(V.begin(),V.end()))

namespace mc {

	class ComboBoxText : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::ComboBoxText* widget;

		public:
			ComboBoxText( Gtk::ComboBoxText* w, json* d);
			~ComboBoxText();

			void notify(Interface* s);
			void broadcast();
			void populate();

			void set_references( std::vector<Interface*> i );
			std::string get_value();
			void set_value( std::vector<std::string> v );
	};

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

			void notify(Interface* s);
			void broadcast();
			void populate();


			void set_marks();
			void set_marks( std::map<double,std::string> m );
			void set_scaler( Interface* i );
			void set_references( std::vector<Interface*> s, std::vector<Interface*> e );
			std::string get_value();
			void set_value( double max, double min, double val );
	};

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

			void notify(Interface* s);
			void broadcast();

			void set_references( std::vector<Interface*> r );
			void set_calculator( std::function<double(std::vector<mc::Interface*>)> f );
			std::string get_value();
			void set_value( double v );
	};

	class Spinner : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::SpinButton* widget;

		public:
			Spinner( Gtk::SpinButton* w, json* d);
			~Spinner();

			void notify(Interface* s);
			void broadcast();

			void set_references( std::vector<Interface*> r );
			std::string get_value();
			void set_value( double d );
	};
}

#endif
