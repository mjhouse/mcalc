/** @file

	@brief		This file contains the main function.

	@details 	The main function initializes the Gtk::Application,
				loads the UI file (glade xml) and launches the
				mcalc::Application to handle user interaction.

	@author Michael House
	@version 0.1 10/19/17
*/

#include <gtkmm/builder.h>
#include "application.hpp"
#include "datastore.hpp"

#include <iostream>

/** The entry point into the application */
int main( int argc, char *argv[] ){
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv,"org.mcalc.base");
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("bin/app.glade");

	Gtk::Window* window = nullptr;
	builder->get_widget("mcalc",window);

	mcalc::Application calc = mcalc::Application(builder,window);
	calc.set_stylesheet("bin/app.css");


	app->run(*window);
	delete window;
	return 0;
}
