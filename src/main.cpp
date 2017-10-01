#include <map>
#include <iostream>
#include <string>
#include <gtkmm.h>

#include "group.hpp"

Glib::RefPtr<Gtk::Builder> builder;
std::map<std::string,double> box_vals;

void on_button_clicked(){
	Gtk::ComboBoxText* combobox;
	Gtk::SpinButton* sfpmbox;
	Gtk::SpinButton* dsbox;
	Gtk::Label* loutput;

	builder->get_widget("fs_materials_input",combobox);
	builder->get_widget("fs_sfpm_input",sfpmbox);
	builder->get_widget("fs_drillsize_input",dsbox);

	std::string ctext = combobox->get_active_text();
	double dSFPM = sfpmbox->get_value();
	double dDrillSize = dsbox->get_value();

	//4 x SFPM / Drill Diameter= RPM
	double rpm = (4.0*dSFPM)/dDrillSize;
	builder->get_widget("fs_materials_output",loutput);
	loutput->set_text(std::to_string(rpm));
}

void on_combo_changed(){
	Gtk::ComboBoxText* combobox;
	Gtk::SpinButton* sfpmbox;
	builder->get_widget("fs_sfpm_input",sfpmbox);
	builder->get_widget("fs_materials_input",combobox);
	sfpmbox->set_value(box_vals[combobox->get_active_text()]);
}

int main( int argc, char *argv[] ){
	auto app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	builder = Gtk::Builder::create_from_file("bin/app.glade");

	Gtk::Window* window = nullptr;
	builder->get_widget("MCalc",window);

	box_vals = {
		{"Aluminum-",250.0},
		{"Bakelite-",125.0},
		{"Plastics-",125.0},
		{"Brass and bronze-",250.0},
		{"Bronze, high tensile",85.0},
		{"Cast iron, chilled",35.0},
		{"Cast iron hard",85.0},
		{"Cast iron soft",125.0},
		{"Magnesium",325.0},
		{"Malleable iron",85.0},
		{"Monel, metal",45.0},
		{"Nickel",50.0},
		{"Steel annealed",65.0},
		{"Forged steel",55.0},
		{"Stainless, easy",65.0},
		{"Stainless, hard",35.0},
		{"Tool steel",55.0},
		{"Slate marble and stone",20.0},
		{"Wrought Iron",55.0}
	};

	Gtk::ComboBoxText* combobox;
	builder->get_widget("fs_materials_input",combobox);

	for ( const auto &pair : box_vals ) {
		combobox->append(pair.first);
	}

	combobox->set_active_text(box_vals.begin()->first);
	on_combo_changed();

	Gtk::Button* btn;
	builder->get_widget("fs_materials_btn",btn);
	btn->signal_clicked().connect(sigc::ptr_fun(&on_button_clicked));
	combobox->signal_changed().connect(sigc::ptr_fun(&on_combo_changed));

	Gtk::Box* box;
	builder->get_widget("feeds_speeds_box",box);
	std::vector<Gtk::Widget*> widgets = box->get_children();
	for( const auto &widget : widgets ){
		std::cout << widget->get_name();
	}

	mcalc::Group* g = new mcalc::Group(builder,{
		"fs_materials_input",
		"fs_sfpm_input",
		"fs_drillsize_input",
		"fs_materials_output"
	});

	/* CSS
	GtkCssProvider* css_provider = nullptr;
	gtk_css_provider_load_from_path (css_provider, "bin/app.css", NULL);
	gtk_style_context_add_provider (window, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	*/
	return app->run(*window);
}
