#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <map>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

typedef void (*on_change)();

namespace mcalc {

	/*
	class Interface {
		private:
			sigc::connection	handler;
			on_change			changed;

		public:
			Interface(){
				changed = nullptr;
				handler = nullptr;
			};
			~Interface(){};
			void update( json d ){};
	};
	*/

	class Application {
		private:
			Glib::RefPtr<Gtk::Builder> builder;
			json datastore;

			// connection references
			sigc::connection		fs_mi;
			sigc::connection		fs_di;
			sigc::connection		fs_hi;
			sigc::connection		fs_ti;
			sigc::connection		fs_gi;
			sigc::connection		fs_vo;
			sigc::connection		fs_fo;
			sigc::connection		fs_ai;

			Gtk::ComboBoxText*		fs_material_input;
			Gtk::ComboBoxText*		fs_designation_input;
			Gtk::ComboBoxText*		fs_hardness_input;
			Gtk::SpinButton*		fs_diameter_input;
			Gtk::ComboBoxText*		fs_tool_input;
			Gtk::ComboBoxText*		fs_grade_input;

			Gtk::Scale*				fs_velocity_output;
			Gtk::Scale*				fs_feedrate_output;
			Gtk::Label*				fs_rpm_output;

			// methods
			void populate( Gtk::ComboBoxText* c, sigc::connection h, json d );
			void set_slider( Gtk::Scale* s, sigc::connection h, json j );

			// handlers
			void on_material_changed();
			void on_designation_changed();
			void on_hardness_changed();
			void on_tool_changed();
			void on_grade_changed();
			void on_velocity_changed();
			void on_feedrate_changed();
			void on_diameter_changed();

		public:
			Application(Glib::RefPtr<Gtk::Builder> b, json d);
			virtual ~Application(){};
	};

}

#endif
