/** @file

	@brief		The class definition file for the main
				application class.

	@details 	Manages the software as a whole and
				initializes all of the widgets and
				the datastore.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <gtkmm.h>

namespace mc {
	class Settings;
	class DataStore;
	class Interface;
	class DummyInterface;
	class ComboBoxText;
	class Spinner;
	class Slider;
	class Output;
}

/** @namespace mcalc

	The mcalc namespace exists only to isolate
	the application from dependencies.
*/
namespace mcalc {

	/**
		The main application manager. Maintains the interface
		wrappers around individual GUI elements (Gtk::Widgets).
	*/
	class Application {
		protected:
			/** The Gtk::Builder that is used to fetch ui elements.*/
			Glib::RefPtr<Gtk::Builder> builder;
			Gtk::Window* window;

			/** The static data used for value lookups. */
			mc::DataStore* datastore;

			/** The user-provided settings. */
			mc::Settings* settings;

			mc::ComboBoxText* fs_material;		/**< material to use */
			mc::ComboBoxText* fs_designation;	/**< AISI/SAE material designation */
			mc::ComboBoxText* fs_hardness;		/**< material hardness */
			mc::ComboBoxText* fs_tool;			/**< cutting tool to use*/
			mc::Spinner*	  fs_diameter;		/**< diameter of the material */
			mc::Slider*		  fs_grade;			/**< grade of material (hard/tough) */
			mc::Slider*		  fs_velocity;		/**< speed of the tool */
			mc::Slider*		  fs_feedrate;		/**< feed rate of material */
			mc::Output*		  fs_rpm;			/**< revolutions per minute */

			mc::DummyInterface* hard;			/**< DummyInterface with value "hard" */
			mc::DummyInterface* tough;			/**< DummyInterface with value "tough" */
			mc::DummyInterface* speed;			/**< DummyInterface with value "speed" */
			mc::DummyInterface* feed;			/**< DummyInterface with value "feed" */

		public:
			/**
				The constructor for the application.

				@param b A Gtk::Builder initialized from a glade file.
				@param w Gtk::Window that the application is managing.
			*/
			Application(Glib::RefPtr<Gtk::Builder> b, Gtk::Window* w);

			/** The application destructor */
			~Application();

			/**
				The css file to style the window with.
				@param f the path to the css file.
			*/
			void set_stylesheet( std::string f );

	};

}

#endif
