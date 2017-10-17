#ifndef MCALC_MCLIB_HPP
#define MCALC_MCLIB_HPP

#include <vector>
#include <iostream>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	class Subscriber {
		public:
			virtual void notify(Subscriber* s)=0;
			virtual void broadcast()=0;
	};

	class Interface {
		public:
			virtual std::string get_value()=0;
	};

	class Broadcaster {
		private:
			std::vector<Subscriber*> subscribers;

			Broadcaster() : subscribers({}) {};

		public:
			static Broadcaster* get_instance();
			void subscribe(Subscriber* s);
			void broadcast(Subscriber* s);
	};

	class ComboBoxText : public Subscriber, public Interface {
		private:
			json* data;
			std::string name;
			std::vector<Interface*> references;
			Gtk::ComboBoxText* widget;
			Broadcaster* broadcaster;

		public:
			ComboBoxText( Gtk::ComboBoxText* w, json* d, std::string n );
			~ComboBoxText();

			void notify(Subscriber* s);
			void broadcast();

			void set_references( std::vector<Interface*> i );
			std::string get_value();
			void set_value( std::vector<std::string> v );
	};

	void set_slider( Gtk::Scale* s, sigc::connection h, json j );
	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d );
	double calculate_rpm ( double v, double d );
}

#endif
