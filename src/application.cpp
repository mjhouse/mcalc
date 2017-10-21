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

		builder->get_widget_derived("fs_material_input",fs_material);
		builder->get_widget_derived("fs_designation_input",fs_designation);
		builder->get_widget_derived("fs_hardness_input",fs_hardness);
		builder->get_widget_derived("fs_tool_input",fs_tool);
		builder->get_widget_derived("fs_rpm_output",fs_rpm);
		builder->get_widget_derived("fs_diameter_input",fs_diameter);

		fs_material->set_data(&datastore);
		fs_designation->set_data(&datastore);
		fs_hardness->set_data(&datastore);
		fs_tool->set_data(&datastore);
		fs_rpm->set_data(&datastore);
		fs_diameter->set_data(&datastore);

		fs_grade 		= get_wrapper<mc::Slider,Gtk::Scale>("fs_grade_output");
		fs_velocity 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_velocity_output");
		fs_feedrate 	= get_wrapper<mc::Slider,Gtk::Scale>("fs_feedrate_output");

		hard 			= _vinterface("hard");
		tough 			= _vinterface("tough");
		speed 			= _vinterface("speed");
		feed 			= _vinterface("feed");


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
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,hard,speed},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,tough,speed}
		);

		// do the same for the feed rate Slider.
		fs_feedrate->set_scaler(fs_grade);
		fs_feedrate->set_references(
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,hard,feed},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,tough,feed}
		);

		// manually broadcast a single ALL event to make the ui initialize itself with
		// starting values.
		mc::Broadcaster* broadcaster = mc::Broadcaster::get_instance();
		broadcaster->broadcast(mc::Event(mc::Event::Type::ALL));
	}


	Application::~Application () {
		delete fs_material; 	fs_material		= nullptr;
		delete fs_designation; 	fs_designation	= nullptr;
		delete fs_hardness; 	fs_hardness 	= nullptr;
		delete fs_tool; 		fs_tool			= nullptr;
		delete fs_diameter; 	fs_diameter 	= nullptr;
		delete fs_grade; 		fs_grade		= nullptr;
		delete fs_velocity; 	fs_velocity 	= nullptr;
		delete fs_feedrate; 	fs_feedrate 	= nullptr;
		delete fs_rpm; 			fs_rpm			= nullptr;

		delete hard; 			hard			= nullptr;
		delete tough; 			tough			= nullptr;
		delete speed; 			speed			= nullptr;
		delete feed; 			feed			= nullptr;
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
