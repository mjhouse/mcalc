#include <map>
#include <iostream>
#include <cmath>
#include <string>
#include <gtkmm.h>
#include <typeinfo>

#include "group.hpp"

Glib::RefPtr<Gtk::Builder> builder;

int main( int argc, char *argv[] ){
	auto app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	builder = Gtk::Builder::create_from_file("bin/app.glade");


	Gtk::Window* window = nullptr;
	builder->get_widget("MCalc",window);

	std::map<std::string,double> md = {
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

	mcalc::Application* calc = new mcalc::Application(
		builder,
		md
	);

	/* CSS
	GtkCssProvider* css_provider = nullptr;
	gtk_css_provider_load_from_path (css_provider, "bin/app.css", NULL);
	gtk_style_context_add_provider (window, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	*/
	return app->run(*window);
}
