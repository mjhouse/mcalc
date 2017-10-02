#include <map>
#include <string>

#include <gtkmm/builder.h>
#include "application.hpp"

int main( int argc, char *argv[] ){
	auto app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("bin/app.glade");


	Gtk::Window* window = nullptr;
	builder->get_widget("MCalc",window);

	mcalc::Application* calc = new mcalc::Application(builder);

	/* CSS
	GtkCssProvider* css_provider = nullptr;
	gtk_css_provider_load_from_path (css_provider, "bin/app.css", NULL);
	gtk_style_context_add_provider (window, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	*/
	return app->run(*window);
}
