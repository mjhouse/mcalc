#include <map>
#include <iostream>
#include <string>

#include <gtkmm/builder.h>
#include "application.hpp"
#include "material.hpp"

int main( int argc, char *argv[] ){
	mcalc::Material mat = mcalc::Material();
	mat.set_type(mcalc::MaterialType::vanadium);
	mat.set_percentage(0.25);

	mcalc::Alloy a = mcalc::Alloy(40.0);
	a.add_material(mcalc::MaterialType::molybdenum,0.26);
	a.add_material(mcalc::MaterialType::vanadium,0.25);
	a.add_material(mcalc::MaterialType::chromium,0.1);

	a.designation();
	/*
	auto app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("bin/app.glade");

	Gtk::Window* window = nullptr;
	builder->get_widget("MCalc",window);

	mcalc::Application* calc = new mcalc::Application(builder);

	//GtkCssProvider* css_provider = nullptr;
	//gtk_css_provider_load_from_path (css_provider, "bin/app.css", NULL);
	//gtk_style_context_add_provider (window, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	return app->run(*window);
	*/
	return 0;
}
