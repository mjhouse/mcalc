#include <iostream>
#include "application.hpp"
#include "mclib.hpp"

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
		b->get_widget("fs_rpm_output",this->fs_rpm_output);

		mc::ComboBoxText* mat = new mc::ComboBoxText(this->fs_material_input, &(this->datastore));
		mc::ComboBoxText* des = new mc::ComboBoxText(this->fs_designation_input, &(this->datastore));
		mc::ComboBoxText* hrd = new mc::ComboBoxText(this->fs_hardness_input, &(this->datastore));
		mc::ComboBoxText* too = new mc::ComboBoxText(this->fs_tool_input, &(this->datastore));
		mc::Slider*		  vel = new mc::Slider(this->fs_velocity_output, &(this->datastore));
		des->set_references(std::vector<mc::Interface*> {mat});
		hrd->set_references(std::vector<mc::Interface*> {mat,des});
		vel->set_references(
			std::vector<mc::Interface*> {mat,des,hrd,too,_VAL("hard"),_VAL("speed")},
			std::vector<mc::Interface*> {mat,des,hrd,too,_VAL("tough"),_VAL("speed")}
		);

		/*
		this->fs_mi = this->fs_material_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_material_changed));
		this->fs_di = this->fs_designation_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_designation_changed));
		this->fs_hi = this->fs_hardness_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_hardness_changed));
		this->fs_ti = this->fs_tool_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_tool_changed));
		this->fs_gi = this->fs_grade_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_grade_changed));
		this->fs_vo = this->fs_velocity_output->signal_value_changed().connect(sigc::mem_fun(*this,
			&Application::on_velocity_changed));
		this->fs_fo = this->fs_feedrate_output->signal_value_changed().connect(sigc::mem_fun(*this,
			&Application::on_feedrate_changed));
		this->fs_ai = this->fs_diameter_input->signal_value_changed().connect(sigc::mem_fun(*this,
			&Application::on_diameter_changed));

		this->fs_material_input->set_active(0);
		this->fs_grade_input->set_active(0);
		*/

	}

	/* -------------------------------------------------------------------------
		Event Handlers */

	void Application::on_material_changed(){
		//json data = this->datastore [this->fs_material_input->get_active_text()];
		//mc::set_comboboxtext( this->fs_designation_input, this->fs_di, data );
	}

	void Application::on_designation_changed(){
		//json data = this->datastore [this->fs_material_input->get_active_text()]
		//							[this->fs_designation_input->get_active_text()];
		//mc::set_comboboxtext( this->fs_hardness_input, this->fs_hi, data );
	}

	void Application::on_hardness_changed(){
		this->on_tool_changed();
	}

	void Application::on_tool_changed(){
		this->on_grade_changed();
	}

	void Application::on_grade_changed(){
		/*
		std::string grade = this->fs_grade_input->get_active_id();
		json data = this->datastore [this->fs_material_input->get_active_text()]
									[this->fs_designation_input->get_active_text()]
									[this->fs_hardness_input->get_active_text()]
									[this->fs_tool_input->get_active_text()];
		if (!data.is_array()) {
			json speed = data[grade]["speed"];
			json feed = data[grade]["feed"];
			if (jnotnull(speed) && jnotnull(feed)) {
				mc::set_slider(this->fs_velocity_output,this->fs_vo,speed);
				mc::set_slider(this->fs_feedrate_output,this->fs_fo,feed);
			}
		}
		*/
		/*
		std::string grade = this->fs_grade_input->get_active_id();
		json data = this->datastore [this->fs_material_input->get_active_text()]
									[this->fs_designation_input->get_active_text()]
									[this->fs_hardness_input->get_active_text()]
									[this->fs_tool_input->get_active_text()];
		if (!data.is_array()) {
			json speed = data[grade]["speed"];
			if (jnotnull(speed)) {
				mc::set_slider(this->fs_velocity_output,this->fs_vo,speed);
			}
		}
		*/
	}

	void Application::on_velocity_changed(){
		/*
		this->fs_rpm_output->set_text(std::to_string(mc::calculate_rpm(
			this->fs_velocity_output->get_value(),
			this->fs_diameter_input->get_value()
		)));
		*/
	}

	void Application::on_feedrate_changed(){
		//std::cout << "feedrate changed" << std::endl;
	}

	void Application::on_diameter_changed(){
		//std::cout << "diameter changed" << std::endl;
	}

}
