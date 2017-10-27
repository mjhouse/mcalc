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

#include "interface.hpp"
#include <gtkmm.h>

namespace mc {

	class Broadcaster;
	class DataStore;

	/**
		The Settings object acts as a collection of
		user-provided values.
	*/
	class Settings : public Subscriber {
		private:
			Glib::RefPtr<Gtk::Builder> builder;
			Gtk::Button* submit;
			DataStore* data;
			Broadcaster* broadcaster;

			std::map<Interface*,std::string> settings;

			Settings();

		public:
			static Settings* get_instance();		/**< Get the singleton instance of settings */
			~Settings();							/**< The destructor */

			/**
				Set the builder object so that Settings can
				load widgets from the ui.
				@param b The builder
			*/
			void set_builder( Glib::RefPtr<Gtk::Builder> b );

			/**
				Link the given Gtk::Button element id to the
				save method.
				@param s The id of the Gtk::Button to use.
			*/
			void set_submit( std::string s );

			/**
				Map an input to a setting value.
				@param s The setting to update.
				@param i The interface to watch.
			*/
			void bind( std::string s, Interface* i );

			/**
				Save the values from the ui into the
				database.
			*/
			void save();

			/**
				Get a key/value map of the current values
				from the ui.
				@return The key/value map
			*/
			std::map<std::string,std::string> values();

			/**
				The method that will receive notifications from
				the broadcaster.
				@param e The event object.
			*/
			void notify(Event* e);
	};

}

#endif
