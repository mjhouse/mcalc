#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <map>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	class Application {
		private:
			Glib::RefPtr<Gtk::Builder>		builder;
			json datastore;

			Gtk::ComboBoxText*		fs_material_input;
			Gtk::ComboBoxText*		fs_designation_input;
			Gtk::SpinButton*		fs_diameter_input;
			Gtk::ComboBoxText*		fs_tool_input;

			Gtk::Scale*				fs_velocity_output;
			Gtk::Scale*				fs_feedrate_output;
			Gtk::Label*				fs_rpm_output;

/*
		protected:
			void on_mill_material_btn_clicked();
			void on_lathe_material_btn_clicked();
			void on_mill_material_changed();
			void on_lathe_values_changed();
			void on_lathe_hc_changed();
			void on_update_designations();
			void on_fs_select_toggled();
*/
		public:
			Application(Glib::RefPtr<Gtk::Builder> b);
			virtual ~Application(){};
	};

}

#endif
