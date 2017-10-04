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

			Gtk::RadioButton*	fs_mill_select;
			Gtk::RadioButton*	fs_lathe_select;

			Gtk::Grid*			fs_mill_grid;
				Gtk::SpinButton*	fs_mill_sfpm_input;
				Gtk::SpinButton*	fs_mill_drillsize_input;
				Gtk::ComboBoxText*	fs_mill_material_input;
				Gtk::Button*		fs_mill_btn;
				Gtk::Label*			fs_mill_rpm_output;

			Gtk::Grid*			fs_lathe_grid;
				Gtk::ComboBoxText*	fs_lathe_material_input;
				Gtk::ComboBoxText*	fs_lathe_material_input1;
				Gtk::ComboBoxText*	fs_lathe_designation_input;
				Gtk::ComboBoxText*	fs_lathe_hc_input;
				Gtk::SpinButton*	fs_lathe_feedrate_input;
				Gtk::SpinButton*	fs_lathe_velocity_input;
				Gtk::Button*		fs_lathe_btn;

				Gtk::Label*			fs_lathe_rpm_output;
				Gtk::Label*			fs_lathe_feedrate_output;
				Gtk::Label*			fs_lathe_velocity_output;

		protected:
			void on_mill_material_btn_clicked();
			void on_lathe_material_btn_clicked();
			void on_mill_material_changed();
			void on_lathe_values_changed();
			void on_lathe_hc_changed();
			void on_update_designations();
			void on_fs_select_toggled();

		public:
			Application(Glib::RefPtr<Gtk::Builder> b);
			virtual ~Application(){};
	};

}

#endif
