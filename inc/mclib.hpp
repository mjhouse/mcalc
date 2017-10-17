#ifndef MCALC_MCLIB_HPP
#define MCALC_MCLIB_HPP

#include <vector>
#include <iostream>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

#define _IN(E,V) (std::find(V.begin(), V.end(), E) != V.end())
#define _VAL(V) (new mc::DummyInterface(V))

namespace mc {

	class Interface {
		public:
			virtual std::string get_value()=0;
	};

	class Subscriber {
		public:
			virtual void notify(Interface* s)=0;
			virtual void broadcast()=0;
	};

	class Broadcaster {
		private:
			std::vector<Subscriber*> subscribers;

			Broadcaster() : subscribers({}) {};

		public:
			static Broadcaster* get_instance();
			void subscribe(Subscriber* s);
			void broadcast(Interface* s);
	};

	class DummyInterface : public Interface {
		private:
			std::string value;
		public:
			DummyInterface( std::string s ){value=s;};
			std::string get_value(){return value;}
	};

	class ComboBoxText : public Subscriber, public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::ComboBoxText* widget;
			Broadcaster* broadcaster;

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

	class Slider : public Subscriber, public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> start_ref;
			std::vector<Interface*> end_ref;
			Gtk::Scale* widget;
			Broadcaster* broadcaster;

		public:
			Slider( Gtk::Scale* w, json* d);
			~Slider();

			void notify(Interface* s);
			void broadcast();
			void populate();

			void set_references( std::vector<Interface*> s, std::vector<Interface*> e );
			std::string get_value();
			void set_value( double max, double min, double val );
	};






	void set_slider( Gtk::Scale* s, sigc::connection h, json j );
	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d );
	double calculate_rpm ( double v, double d );
}

#endif
