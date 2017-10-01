#include <vector>

#include "group.hpp"

namespace mcalc {

	/* -------------------------------------------------------------------------
		Constructors/Destructors */
	Application::Application(Glib::RefPtr<Gtk::Builder> b, std::map<std::string,double> d ){
		this->builder = b;
		this->material_data = d;

		b->get_widget("fs_sfpm_input",this->fs_sfpm_input);
		b->get_widget("fs_drillsize_input",this->fs_drillsize_input);
		b->get_widget("fs_materials_btn",this->fs_materials_btn);
		b->get_widget("fs_materials_input",this->fs_materials_input);
		b->get_widget("fs_materials_output",this->fs_materials_output);

		/* -------------------------------------------------------------
		*	Initialize widgets that need data */
		for ( const auto &pair : d ) {
			this->fs_materials_input->append(pair.first);
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
		this->fs_sfpm_input->set_value(this->material_data[this->fs_materials_input->get_active_text()]);
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
