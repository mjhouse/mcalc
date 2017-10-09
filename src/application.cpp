#include <iostream>

#include "datastore.hpp"
#include "application.hpp"

namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b){
		this->builder = b;
		this->datastore = get_data();


		b->get_widget("fs_material_input",this->fs_material_input);
		b->get_widget("fs_designation_input",this->fs_designation_input);
		b->get_widget("fs_diameter_input",this->fs_diameter_input);
		b->get_widget("fs_tool_input",this->fs_tool_input);
		b->get_widget("fs_velocity_output",this->fs_velocity_output);
		b->get_widget("fs_feedrate_output",this->fs_feedrate_output);
		b->get_widget("fs_rpm_output",this->fs_rpm_output);

		/* -------------------------------------------------------------
		*	Initialize widgets that need data

		// load fs_mill_data into combobox "fs_mill_material_input"
		json m_data = this->datastore["fs_mill_data"];
		for (json::iterator it = m_data.begin(); it != m_data.end(); ++it) {
			this->fs_mill_material_input->append(it.key());
		}

		// load fs_lathe_data into combobox "fs_lathe_material_input"
		json lf_data = this->datastore["fs_lathe_data"]["feedrate"];
		for (json::iterator it = lf_data.begin(); it != lf_data.end(); ++it) {
			this->fs_lathe_material_input->append(it.key());
		}

		// load fs_lathe_data into combobox "fs_lathe_material_input1"
		json lv_data = this->datastore["fs_lathe_data"]["velocity"];
		for (json::iterator it = lv_data.begin(); it != lv_data.end(); ++it) {
			this->fs_lathe_material_input1->append(it.key());
		}

		// set the initial combobox values
		this->fs_mill_material_input->set_active(0);
		this->fs_lathe_material_input->set_active(0);
		this->fs_lathe_material_input1->set_active(0);

		// set the intial calculated values
		this->on_mill_material_changed();
		this->on_lathe_values_changed();
		this->on_update_designations();

		// hide the lathe grid
		this->fs_lathe_grid->hide();


		/* -------------------------------------------------------------
		*	Connect event handlers to events
		this->fs_mill_material_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_mill_material_changed));
		this->fs_lathe_material_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_lathe_values_changed));
		this->fs_lathe_hc_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_lathe_values_changed));
		this->fs_lathe_hc_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_lathe_hc_changed));
		this->fs_lathe_material_input1->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_lathe_hc_changed));
		this->fs_lathe_material_input1->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_update_designations));
		this->fs_mill_btn->signal_clicked().connect(sigc::mem_fun(*this,
			&Application::on_mill_material_btn_clicked));
		this->fs_lathe_btn->signal_clicked().connect(sigc::mem_fun(*this,
			&Application::on_lathe_material_btn_clicked));
		this->fs_mill_select->signal_toggled().connect(sigc::mem_fun(*this,
			&Application::on_fs_select_toggled));

		*/
	}

	/* -------------------------------------------------------------------------
		Event Handlers */

	void Application::on_mill_material_changed(){
		json data = this->datastore["fs_mill_data"];
		this->fs_mill_sfpm_input->set_value(data[this->fs_mill_material_input->get_active_text()]);
	}

/*
	void Application::on_lathe_values_changed(){
		std::string mat = this->fs_lathe_material_input->get_active_text();
		std::string hc = this->fs_lathe_hc_input->get_active_text();
		json data = this->datastore["fs_lathe_data"]["feedrate"][mat][hc];

		float h = data["high"];
		float l = data["low"];
		float mid = (h - l)/2.0 + l;
		this->fs_lathe_feedrate_input->set_value(mid);

		char buffer[20];
		sprintf(buffer, "%.3f - %.3f", l, h);
		this->fs_lathe_feedrate_output->set_text(std::string(buffer));
	}

	void Application::on_lathe_hc_changed(){
		// fs_lathe_hc_input
		std::string hc = this->fs_lathe_hc_input->get_active_text();
		std::string mat = this->fs_lathe_material_input1->get_active_text();
		json data = this->datastore["fs_lathe_data"]["velocity"][mat][hc];

		float h = data["high"];
		float l = data["low"];
		float mid = (h - l)/2.0 + l;
		this->fs_lathe_velocity_input->set_value(mid);

		char buffer[20];
		sprintf(buffer, "%.3f - %.3f", l, h);
		this->fs_lathe_velocity_output->set_text(std::string(buffer));
	}

	void Application::on_mill_material_btn_clicked(){
		double s = this->fs_mill_sfpm_input->get_value();
		double d = this->fs_mill_drillsize_input->get_value();
		double rpm = (4.0*s)/d;
		if(!std::isinf(rpm)){
			this->fs_mill_rpm_output->set_text(std::to_string(rpm));
		}
	}

	void Application::on_update_designations(){
		gtk_combo_box_text_remove_all(this->fs_lathe_designation_input->gobj());

		std::string mat = this->fs_lathe_material_input1->get_active_text();
		json d = this->datastore["fs_lathe_data"]["velocity"][mat]["Designations"];

		for (json::iterator it = d.begin(); it != d.end(); ++it) {
			this->fs_lathe_designation_input->append(it->get<std::string>());
		}

		this->fs_lathe_designation_input->set_active(0);
	}

	void Application::on_lathe_material_btn_clicked(){
		std::cout << "Lathe Btn Clicked" << std::endl;
	}

	void Application::on_fs_select_toggled(){
		int is_lathe = this->fs_lathe_select->get_active();
		if(is_lathe){
			this->fs_lathe_grid->show();
			this->fs_mill_grid->hide();
		} else {
			this->fs_mill_grid->show();
			this->fs_lathe_grid->hide();
		}
	}
*/
}
