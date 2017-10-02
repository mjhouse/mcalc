#include <iostream>

#include "datastore.hpp"
#include "application.hpp"

namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b){
		this->builder = b;
		this->datastore = get_data();

		b->get_widget("fs_materials_grid",this->fs_materials_grid);
			b->get_widget("fs_mill_select",this->fs_mill_select);
			b->get_widget("fs_lathe_select",this->fs_lathe_select);
			b->get_widget("fs_sfpm_input",this->fs_sfpm_input);
			b->get_widget("fs_drillsize_input",this->fs_drillsize_input);
			b->get_widget("fs_materials_btn",this->fs_materials_btn);
			b->get_widget("fs_materials_input",this->fs_materials_input);
			b->get_widget("fs_materials_output",this->fs_materials_output);

		b->get_widget("fs_lathe_grid",this->fs_lathe_grid);


		/* -------------------------------------------------------------
		*	Initialize widgets that need data */

		// load fs_materials_data into combobox "fs_materials_input"
		json data = this->datastore["fs_materials_data"];
		for (json::iterator it = data.begin(); it != data.end(); ++it) {
			this->fs_materials_input->append(it.key());
		}

		// set the active value in fs_materials_input
		this->fs_materials_input->set_active(0);
		this->on_material_input_changed();

		// hide the lathe grid
		this->fs_lathe_grid->hide();


		/* -------------------------------------------------------------
		*	Connect event handlers to events */
		this->fs_materials_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_material_input_changed));
		this->fs_materials_btn->signal_clicked().connect(sigc::mem_fun(*this,
			&Application::on_material_sfpm_button_clicked));

		this->fs_mill_select->signal_toggled().connect(sigc::mem_fun(*this,
			&Application::on_fs_select_toggled));

	}

	/* -------------------------------------------------------------------------
		Event Handlers */
	void Application::on_material_input_changed(){
		json data = this->datastore["fs_materials_data"];
		this->fs_sfpm_input->set_value(data[this->fs_materials_input->get_active_text()]);
	}

	void Application::on_material_sfpm_button_clicked(){
		double s = this->fs_sfpm_input->get_value();
		double d = this->fs_drillsize_input->get_value();
		double rpm = (4.0*s)/d;
		if(!std::isinf(rpm)){
			this->fs_materials_output->set_text(std::to_string(rpm));
		}
	}

	void Application::on_fs_select_toggled(){
		int is_lathe = this->fs_lathe_select->get_active();
		if(is_lathe){
			this->fs_lathe_grid->show();
			this->fs_materials_grid->hide();
		} else {
			this->fs_materials_grid->show();
			this->fs_lathe_grid->hide();
		}
	}

}
