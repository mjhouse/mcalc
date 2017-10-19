#include <iostream>
#include <functional>

#include "application.hpp"

#include "interface.hpp"
#include "slider.hpp"
#include "output.hpp"
#include "spinner.hpp"
#include "comboboxtext.hpp"


namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b, json d){
		this->builder = b;
		this->datastore = d;

		fs_material 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_material_input");
		fs_designation 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_designation_input");
		fs_hardness 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_hardness_input");
		fs_tool 		= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_tool_input");
		fs_diameter 	= get_wrapper<mc::Spinner,Gtk::SpinButton>("fs_diameter_input");
		fs_grade 		= get_wrapper<mc::Slider,Gtk::Scale>("fs_grade_output");
		fs_velocity 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_velocity_output");
		fs_feedrate 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_feedrate_output");
		fs_rpm 			= get_wrapper<mc::Output,Gtk::Label>("fs_rpm_output");

		fs_designation->set_references(std::vector<mc::Interface*> {fs_material});
		fs_hardness->set_references(std::vector<mc::Interface*> {fs_material,fs_designation});
		fs_rpm->set_references(std::vector<mc::Interface*> {fs_velocity,fs_diameter,fs_grade});

		fs_rpm->set_calculator([](std::vector<mc::Interface*> i){
			if(i.size()>=2){
				double v = std::stod(i[0]->get_value());
				double d = std::stod(i[1]->get_value());
				double fs_rpm = (4.0*v)/d;
				if(!std::isinf(fs_rpm)){ return fs_rpm; };
			}
			return 0.0;
		});

		fs_grade->set_marks(std::map<double,std::string> {{0.0,"Tough"},{100.0,"Hard"},{50.0,""}});

		fs_velocity->set_scaler(fs_grade);
		fs_velocity->set_references(
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("hard"),_vinterface("speed")},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("tough"),_vinterface("speed")}
		);

		fs_feedrate->set_scaler(fs_grade);
		fs_feedrate->set_references(
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("hard"),_vinterface("feed")},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("tough"),_vinterface("feed")}
		);

	}

	/* -------------------------------------------------------------------------
		Functions */

	// get_wrapper: create an mc::Interface around a widget
	template <class A,class B>
	A* Application::get_wrapper ( std::string n ) {
		B* tmp; builder->get_widget(n,tmp);
		return new A(tmp, &(datastore));
	}

}
