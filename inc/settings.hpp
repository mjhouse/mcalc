/** @file

	@brief		The class definition file for the
				settings class.

	@details 	Manages user-provided settings, flags and values.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_SETTINGS_HPP
#define MCALC_SETTINGS_HPP

#include <gtkmm.h>

namespace mc {

	class Interface;

	/**
		The Settings object acts as a collection of
		user-provided values.
	*/
	class Settings {
		private:
			Glib::RefPtr<Gtk::Builder> ui;
			std::vector<std::string> inputs;

			Settings();

		public:
			static Settings* get_instance();		/**< Get the singleton instance of settings */
			~Settings();							/**< The destructor */

			/**
				set the settings input widgets
				@param b The builder to fetch widgets from.
			*/
			void set_ui( Glib::RefPtr<Gtk::Builder> b );

			/**
				set the settings input widgets
				@param i The ui widgets
			*/
			void set_inputs( std::vector<std::string> i );
	};

}

#endif
