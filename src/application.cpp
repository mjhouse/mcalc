#include <iostream>
#include "application.hpp"

#define get(X) (this->X->get_active_text())

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

		json m_data = this->datastore;
		for (json::iterator it = m_data.begin(); it != m_data.end(); ++it) {
			this->fs_material_input->append(it.key());
		}

		this->fs_material_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_material_changed));
		this->fs_designation_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_designation_changed));
		this->fs_hardness_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_hardness_changed));
		this->fs_tool_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_tool_changed));

		this->fs_material_input->set_active(0);
	}

	/* -------------------------------------------------------------------------
		Application Methods */
	void Application::populate( Gtk::ComboBoxText* c, json d ){
		gtk_combo_box_text_remove_all(c->gobj());
		for (json::iterator it = d.begin(); it != d.end(); ++it) {
			json j = *it;
			if (!j.is_primitive()) {
				c->append(it.key());
			} else {
				c->append(it->get<std::string>());
			}
		}
		c->set_active(0);
	}

	/* -------------------------------------------------------------------------
		Event Handlers */

	void Application::on_material_changed(){
		json data = this->datastore [get(fs_material_input)];
		this->populate( this->fs_designation_input, data );
	}

	void Application::on_designation_changed(){
		json data = this->datastore [get(fs_material_input)]
									[get(fs_designation_input)];
		this->populate(	this->fs_hardness_input, data );
	}

	void Application::on_hardness_changed(){
		json data = this->datastore [get(fs_material_input)]
									[get(fs_designation_input)]
									[get(fs_hardness_input)];
		this->populate( this->fs_tool_input, data );
	}

	void Application::on_tool_changed(){
		json data = this->datastore [get(fs_material_input)]
									[get(fs_designation_input)]
									[get(fs_hardness_input)]
									[get(fs_tool_input)];
		std::cout << data << std::endl;
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
