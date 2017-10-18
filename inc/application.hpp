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
			json datastore;

			// connection references
			sigc::connection		fs_mi;
			sigc::connection		fs_di;
			sigc::connection		fs_hi;
			sigc::connection		fs_ti;
			sigc::connection		fs_vo;
			sigc::connection		fs_fo;
			sigc::connection		fs_ai;

			Gtk::ComboBoxText*		fs_material_input;
			Gtk::ComboBoxText*		fs_designation_input;
			Gtk::ComboBoxText*		fs_hardness_input;
			Gtk::SpinButton*		fs_diameter_input;
			Gtk::ComboBoxText*		fs_tool_input;

			Gtk::Scale*				fs_velocity_output;
			Gtk::Scale*				fs_feedrate_output;
			Gtk::Scale*				fs_grade_output;
			Gtk::Label*				fs_rpm_output;

		public:
			Application(Glib::RefPtr<Gtk::Builder> b, json d);
			virtual ~Application(){};
	};

}

#endif
