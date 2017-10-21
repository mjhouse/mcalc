/** @file

	@brief		The class definition file for the main
				application class.

	@details 	Manages the software as a whole and
				initializes all of the widgets and
				the datastore.

	@author Michael House
	@version 0.1 10/19/17
*/

#ifndef MCALC_APPLICATION_HPP
#define MCALC_APPLICATION_HPP

#include <map>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

namespace mc {
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

			/** The generated tabls and other data used for lookups. */
			json datastore;

			mc::ComboBoxText* fs_material;		/**< material to use */
			mc::ComboBoxText* fs_designation;	/**< AISI/SAE material designation */
			mc::ComboBoxText* fs_hardness;		/**< material hardness */
			mc::ComboBoxText* fs_tool;			/**< cutting tool to use*/
			mc::Spinner*	  fs_diameter;		/**< diameter of the material */
			mc::Slider*		  fs_grade;			/**< grade of material (hard/tough) */
			mc::Slider*		  fs_velocity;		/**< speed of the tool */
			mc::Slider*		  fs_feedrate;		/**< feed rate of material */
			mc::Output*		  fs_rpm;			/**< revolutions per minute */

			mc::DummyInterface* hard;
			mc::DummyInterface* tough;
			mc::DummyInterface* speed;
			mc::DummyInterface* feed;
			
		public:
			/**
				The constructor for the application.

				@param b A Gtk::Builder initialized from a glade file.
				@param d JSON data used for value lookups and populating the ui.
			*/
			Application(Glib::RefPtr<Gtk::Builder> b, json d);

			/** The application destructor */
			~Application();

			/**
				A templated function that generates Interfaces
				for given Gtk::Widgets.

				@tparam A The Interface subclass to create
				@tparam B The Gtk::Widget type to look up

				@param n The name to lookup in builder (Gtk::Builder)
				@return The new Interface object.
			 */
			template <class A,class B>
			A* get_wrapper ( std::string n );
	};

}

#endif
