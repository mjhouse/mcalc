#include <iostream>
#include <functional>

#include "mclib.hpp"
#include "interface.hpp"
#include "application.hpp"

#define jnotnull(X) (X.type() != json::value_t::null)

namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b, json d){
		this->builder = b;
		this->datastore = d;

		b->get_widget("fs_material_input",this->fs_material_input);
		b->get_widget("fs_designation_input",this->fs_designation_input);
		b->get_widget("fs_hardness_input",this->fs_hardness_input);
		b->get_widget("fs_diameter_input",this->fs_diameter_input);
		b->get_widget("fs_tool_input",this->fs_tool_input);
		b->get_widget("fs_velocity_output",this->fs_velocity_output);
		b->get_widget("fs_feedrate_output",this->fs_feedrate_output);
		b->get_widget("fs_grade_output",this->fs_grade_output);
		b->get_widget("fs_rpm_output",this->fs_rpm_output);

		mc::ComboBoxText* mat = new mc::ComboBoxText(this->fs_material_input, &(this->datastore));
		mc::ComboBoxText* des = new mc::ComboBoxText(this->fs_designation_input, &(this->datastore));
		mc::ComboBoxText* hrd = new mc::ComboBoxText(this->fs_hardness_input, &(this->datastore));
		mc::ComboBoxText* too = new mc::ComboBoxText(this->fs_tool_input, &(this->datastore));
		mc::Spinner*	  dia = new mc::Spinner(this->fs_diameter_input, &(this->datastore));
		mc::Slider*		  gra = new mc::Slider(this->fs_grade_output, &(this->datastore));
		mc::Slider*		  vel = new mc::Slider(this->fs_velocity_output, &(this->datastore));
		mc::Slider*		  fee = new mc::Slider(this->fs_feedrate_output, &(this->datastore));
		mc::Output*		  rpm = new mc::Output(this->fs_rpm_output, &(this->datastore));

		des->set_references(std::vector<mc::Interface*> {mat});
		hrd->set_references(std::vector<mc::Interface*> {mat,des});
		rpm->set_references(std::vector<mc::Interface*> {vel,dia});

		rpm->set_calculator([](std::vector<mc::Interface*> i){
			if(i.size()>=2){
				double v = std::stod(i[0]->get_value());
				double d = std::stod(i[1]->get_value());
				double rpm = (4.0*v)/d;
				if(!std::isinf(rpm)){ return rpm; };
			}
			return 0.0;
		});

		gra->set_marks(std::map<double,std::string> {{0.0,"Tough"},{100.0,"Hard"},{50.0,""}});

		vel->set_scaler(gra);
		vel->set_references(
			std::vector<mc::Interface*> {mat,des,hrd,too,_vinterface("hard"),_vinterface("speed")},
			std::vector<mc::Interface*> {mat,des,hrd,too,_vinterface("tough"),_vinterface("speed")}
		);

		fee->set_scaler(gra);
		fee->set_references(
			std::vector<mc::Interface*> {mat,des,hrd,too,_vinterface("hard"),_vinterface("feed")},
			std::vector<mc::Interface*> {mat,des,hrd,too,_vinterface("tough"),_vinterface("feed")}
		);

	}

}
