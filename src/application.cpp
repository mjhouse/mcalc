#include <iostream>
#include <functional>

#include "application.hpp"
#include "broadcaster.hpp"

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

		// generate wrapping Interface's for each ui element that we need to interact
		// with.
		fs_material 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_material_input");
		fs_designation 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_designation_input");
		fs_hardness 	= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_hardness_input");
		fs_tool 		= get_wrapper<mc::ComboBoxText,Gtk::ComboBoxText>("fs_tool_input");
		fs_diameter 	= get_wrapper<mc::Spinner,Gtk::SpinButton>("fs_diameter_input");
		fs_grade 		= get_wrapper<mc::Slider,Gtk::Scale>("fs_grade_output");
		fs_velocity 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_velocity_output");
		fs_feedrate 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_feedrate_output");
		fs_rpm 			= get_wrapper<mc::Output,Gtk::Label>("fs_rpm_output");

		// set referenced ui elements. when the references change their values,
		// they broadcast a message, and any Interface that has them as a reference
		// will also update themselves.
		fs_designation->set_references(std::vector<mc::Interface*> {fs_material});
		fs_hardness->set_references(std::vector<mc::Interface*> {fs_material,fs_designation});
		fs_rpm->set_references(std::vector<mc::Interface*> {fs_velocity,fs_diameter,fs_grade});

		// Outputs accept calculators (lambda functions) that generate their values given
		// the values of their referenced Interfaces. This is the function that generates
		// the RPM in the feeds/speeds tab of the ui. It assumes that the first ref is velocity
		// and the second is the diameter of the tool used.
		fs_rpm->set_calculator([](std::vector<mc::Interface*> i){
			if(i.size()>=2){
				double v = std::stod(i[0]->get_value());
				double d = std::stod(i[1]->get_value());
				double fs_rpm = (4.0*v)/d;
				if(!std::isinf(fs_rpm)){ return fs_rpm; };
			}
			return 0.0;
		});

		// Sliders can have fixed marks set. these are the marks for the Grade slider.
		fs_grade->set_marks(std::map<double,std::string> {{0.0,"Tough"},{100.0,"Hard"},{50.0,""}});

		// The scaler adjusts the max and min between two possible sets of max and min,
		// effectively moving the 'window' of the slider up or down.
		//
		// There are two references for the slider, because there are two possible max/min pairs
		// that the scaler adjusts between.
		fs_velocity->set_scaler(fs_grade);
		fs_velocity->set_references(
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("hard"),_vinterface("speed")},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("tough"),_vinterface("speed")}
		);

		// do the same for the feed rate Slider.
		fs_feedrate->set_scaler(fs_grade);
		fs_feedrate->set_references(
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("hard"),_vinterface("feed")},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,_vinterface("tough"),_vinterface("feed")}
		);

		// manually broadcast a single ALL event to make the ui initialize itself with
		// starting values.
		mc::Broadcaster* broadcaster = mc::Broadcaster::get_instance();
		broadcaster->broadcast(mc::Event(mc::Event::Type::ALL));
	}


	Application::~Application () {
		delete fs_material;
		delete fs_designation;
		delete fs_hardness;
		delete fs_tool;
		delete fs_diameter;
		delete fs_grade;
		delete fs_velocity;
		delete fs_feedrate;
		delete fs_rpm;
	}
	/* -------------------------------------------------------------------------
		Functions */

	/* -------------------------------------------------------------------------
		get_wrapper:
			create an mc::Interface around a widget, where A is the
			Interface to create, and B is the type of widget to use.

			std::string n:
				the name of the ui widget to look up.

			A*:
				a pointer to the newly created Interface
	*/
	template <class A,class B>
	A* Application::get_wrapper ( std::string n ) {
		B* tmp;
		builder->get_widget(n,tmp);
		return new A(tmp, &(datastore));
	}

}
