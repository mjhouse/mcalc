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

			Gtk::SpinButton*	fs_sfpm_input;
			Gtk::SpinButton*	fs_drillsize_input;
			Gtk::ComboBoxText*	fs_materials_input;
			Gtk::Button*		fs_materials_btn;
			Gtk::Label*			fs_materials_output;

		protected:
			void on_material_sfpm_button_clicked();
			void on_material_input_changed();

		public:
			Application(Glib::RefPtr<Gtk::Builder> b);
			virtual ~Application(){};
	};

}

#endif
