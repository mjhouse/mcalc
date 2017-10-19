#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <map>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mc {
	class ComboBoxText;
	class Spinner;
	class Slider;
	class Output;
}

namespace mcalc {

	class Application {
		private:
			Glib::RefPtr<Gtk::Builder> builder;
			json datastore;

			mc::ComboBoxText* fs_material;
			mc::ComboBoxText* fs_designation;
			mc::ComboBoxText* fs_hardness;
			mc::ComboBoxText* fs_tool;
			mc::Spinner*	  fs_diameter;
			mc::Slider*		  fs_grade;
			mc::Slider*		  fs_velocity;
			mc::Slider*		  fs_feedrate;
			mc::Output*		  fs_rpm;

		public:
			Application(Glib::RefPtr<Gtk::Builder> b, json d);
			virtual ~Application(){};

			template <class A,class B>
			A* get_wrapper ( std::string n );
	};

}

#endif
