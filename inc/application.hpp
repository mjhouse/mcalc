#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <map>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	class Application {
		private:
			Glib::RefPtr<Gtk::Builder> builder;
			std::map<std::string,json> datastore;

			Gtk::ComboBoxText*		fs_material_input;
			Gtk::ComboBoxText*		fs_designation_input;
			Gtk::ComboBoxText*		fs_hardness_input;
			Gtk::SpinButton*		fs_diameter_input;
			Gtk::ComboBoxText*		fs_tool_input;

			Gtk::Scale*				fs_velocity_output;
			Gtk::Scale*				fs_feedrate_output;
			Gtk::Label*				fs_rpm_output;

			// methods
			void populate( Gtk::ComboBoxText* c, json d );

			// handlers
			void on_material_changed();
			void on_designation_changed();

		public:
			Application(Glib::RefPtr<Gtk::Builder> b, std::map<std::string,json> d);
			virtual ~Application(){};
	};

}

#endif