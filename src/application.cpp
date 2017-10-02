#include <iostream>

#include "datastore.hpp"
#include "application.hpp"

namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b){
		this->builder = b;
		this->datastore = get_data();

		b->get_widget("fs_sfpm_input",this->fs_sfpm_input);
		b->get_widget("fs_drillsize_input",this->fs_drillsize_input);
		b->get_widget("fs_materials_btn",this->fs_materials_btn);
		b->get_widget("fs_materials_input",this->fs_materials_input);
		b->get_widget("fs_materials_output",this->fs_materials_output);

		/* -------------------------------------------------------------
		*	Initialize widgets that need data */
		json data = this->datastore["fs_materials_data"];
		for (json::iterator it = data.begin(); it != data.end(); ++it) {
			this->fs_materials_input->append(it.key());
		}


		/* -------------------------------------------------------------
		*	Connect event handlers to events */
		this->fs_materials_input->signal_changed().connect(sigc::mem_fun(*this,
			&Application::on_material_input_changed));
		this->fs_materials_btn->signal_clicked().connect(sigc::mem_fun(*this,
			&Application::on_material_sfpm_button_clicked));

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

}
