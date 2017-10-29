#include <functional>

#include "application.hpp"
#include "broadcaster.hpp"

#include "interface.hpp"
#include "slider.hpp"
#include "output.hpp"
#include "spinner.hpp"
#include "comboboxtext.hpp"
#include "filechooserbutton.hpp"
#include "datastore.hpp"
#include "settings.hpp"


namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b, Gtk::Window* w){
		this->builder = b;
		this->window = w;
		this->datastore = mc::DataStore::get_instance();
		this->settings = mc::Settings::get_instance();

		// generate wrapping Interface's for each ui element that we need to interact
		// with.

		builder->get_widget_derived("fs_material_input",fs_material);
		builder->get_widget_derived("fs_designation_input",fs_designation);
		builder->get_widget_derived("fs_hardness_input",fs_hardness);
		builder->get_widget_derived("fs_tool_input",fs_tool);
		builder->get_widget_derived("fs_rpm_output",fs_rpm);
		builder->get_widget_derived("fs_diameter_input",fs_diameter);

		builder->get_widget_derived("fs_grade_output",fs_grade);
		builder->get_widget_derived("fs_velocity_output",fs_velocity);
		builder->get_widget_derived("fs_feedrate_output",fs_feedrate);

		hard 			= _vinterface("hard");
		tough 			= _vinterface("tough");

		fs_material->set_column("description");
		fs_designation->set_column("designation");
		fs_hardness->set_column("hardness");
		fs_tool->set_column("tool");
		fs_grade->set_column("grade");

		hard->set_column("grade");
		tough->set_column("grade");


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
		fs_velocity->set_columns(std::vector<std::string>{"max_sfpm","min_sfpm"});
		fs_velocity->set_references( // SPEED
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,hard},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,tough}
		);

		// do the same for the feed rate Slider.
		fs_feedrate->set_scaler(fs_grade);
		fs_feedrate->set_columns(std::vector<std::string>{"max_feed","min_feed"});
		fs_feedrate->set_references( // FEED
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,hard},
			std::vector<mc::Interface*> {fs_material,fs_designation,fs_hardness,fs_tool,tough}
		);

		// Bind the settings input elements and the settings 'Save' button
		// to the Settings object.
		settings->set_builder(b);
		settings->set_submit("s_save_btn");

		settings->load("default");

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

		delete hard;
		delete tough;
	}

	void Application::set_stylesheet( std::string f ){
		Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
		Glib::RefPtr<Gtk::StyleContext> style_context = Gtk::StyleContext::create();

		//load our css file, wherever that may be hiding
		if(css_provider->load_from_path(f)){
			Glib::RefPtr<Gdk::Screen> screen = window->get_screen();
			style_context->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
		}
	}

}
