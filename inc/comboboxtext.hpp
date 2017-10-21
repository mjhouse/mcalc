/** @file

	@brief		The class definition file for the
				comboboxtext class.

	@details 	Acts as a wrapper for a Gtk::ComboBoxText,
				broadcasting state changes and updating
				data in the combobox.

	@author Michael House
	@version 0.1 10/19/17
*/

#ifndef MCALC_COMBOBOXTEXT_HPP
#define MCALC_COMBOBOXTEXT_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

namespace mc {

	class Interface;
	class Event;

	/**
		ComboBoxText wraps a Gtk::ComboBoxText widget, updates
		it when dependent values change, and broadcasts an
		event when the user selects a value.
	*/
	class ComboBoxText : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::ComboBoxText* widget;

		public:
			/**
				Constructor
				@param w the Gtk::ComboBoxText to wrap
				@param d Pointer to the json datastore
			*/
			ComboBoxText( Gtk::ComboBoxText* w, json* d);

			/** The destructor */
			~ComboBoxText();

			/**
				Method used to update the ComboBoxText by the broadcaster.
				@param e Event received from broadcaster
			*/
			void notify(Event* e);

			/**
				Sends out a change event.
			*/
			void broadcast();

			/**
				Populates the UI with values from the datastore.
			*/
			void populate();

			/**
				Add references to the interface that will trigger
				the ComboBoxText to update when they change.
				@param i A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<Interface*> i );

			/**
				Get the current value of the ComboBoxText
			*/
			std::string get_value();

			/**
				Set the ComboBoxText contents
				@param v A vector of strings to use as entries
			*/
			void set_value( std::vector<std::string> v );

	};

}

#endif
