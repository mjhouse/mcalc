#include <iostream>
#include <string>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/liststore.h>
#include <string.h>

Glib::RefPtr<Gtk::Builder> builder;

void on_button_clicked(){
	Gtk::ComboBoxText* combobox;
	Gtk::Entry* sfpmbox;

	builder->get_widget("fs_materials_input",combobox);
	builder->get_widget("fs_sfpm_input",sfpmbox);
	
	std::cout << "test" << std::endl;
}

int main( int argc, char *argv[] ){
	auto app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	builder = Gtk::Builder::create_from_file("bin/app.glade");

	Gtk::Window* window = nullptr;
	builder->get_widget("MCalc",window);

	std::string box_vals[19] = {
		"Aluminum-",
		"Bakelite-",
		"Plastics-",
		"Brass and bronze-",
		"Bronze, high tensile",
		"Cast iron, chilled",
		"Cast iron hard",
		"Cast iron soft",
		"Magnesium",
		"Malleable iron",
		"Monel, metal",
		"Nickel",
		"Steel annealed",
		"Forged steel",
		"Stainless, easy",
		"Stainless, hard",
		"Tool steel",
		"Slate marble and stone",
		"Wrought Iron"
	};

	Gtk::ComboBoxText* combobox;
	builder->get_widget("fs_materials_input",combobox);

	for (int i = 0; i < 19; i++) {
		std::string val = box_vals[i];
		combobox->append(val);
	}

	combobox->set_active_text(box_vals[0]);

	Gtk::Button* btn;
	builder->get_widget("fs_materials_btn",btn);
	btn->signal_clicked().connect(sigc::ptr_fun(&on_button_clicked));


	/* CSS
	GtkCssProvider* css_provider = nullptr;
	gtk_css_provider_load_from_path (css_provider, "bin/app.css", NULL);
	gtk_style_context_add_provider (window, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	*/
	return app->run(*window);
}
