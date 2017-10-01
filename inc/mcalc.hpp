#ifndef GROUP_HPP
#define GROUP_HPP

#include <gtkmm.h>
#include <map>

namespace mcalc {

	class Application {
		private:
			Glib::RefPtr<Gtk::Builder>		builder;
			std::map<std::string,double>	material_data;

			Gtk::SpinButton*	fs_sfpm_input;
			Gtk::SpinButton*	fs_drillsize_input;
			Gtk::ComboBoxText*	fs_materials_input;
			Gtk::Button*		fs_materials_btn;
			Gtk::Label*			fs_materials_output;

		protected:
			void on_material_sfpm_button_clicked();
			void on_material_input_changed();

		public:
			Application(Glib::RefPtr<Gtk::Builder> b, std::map<std::string,double> d );
			virtual ~Application(){};
	};

}

#endif
