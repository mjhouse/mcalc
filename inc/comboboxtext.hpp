/** @file

	@brief		The class definition file for the
				comboboxtext class.

	@details 	Acts as a wrapper for a Gtk::ComboBoxText,
				broadcasting state changes and updating
				data in the combobox.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_COMBOBOXTEXT_HPP
#define MCALC_COMBOBOXTEXT_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

namespace mc {

	class Event;

	/**
		ComboBoxText wraps a Gtk::ComboBoxText widget, updates
		it when dependent values change, and broadcasts an
		event when the user selects a value.
	*/
	class ComboBoxText : public mc::Interface, public Gtk::ComboBoxText {
		private:
			bool blocked;
			const Glib::RefPtr<Gtk::Builder>& glade_ref;
			std::vector<mc::Interface*> references;

		public:
			/**
				Constructor for the Gtk::Builder
				@param cobject A base object typedef
				@param refGlade A reference to the builder.
			*/
			ComboBoxText(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

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
			virtual void on_changed();

			/**
				Populates the UI with values from the datastore.
			*/
			void populate();

			/**
				Add references to the interface that will trigger
				the ComboBoxText to update when they change.
				@param i A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<mc::Interface*> i );

			/**
				Get the current value of the ComboBoxText
			*/
			std::string get_value();

			/**
				Stop/start broadcasting events
				@param b True allows broadcasts, false dis-allows.
			*/
			void block( bool b );

			/**
				Set the ComboBoxText contents
				@param v A vector of Interface objects to fetch path from datastore
			*/
			void set_value( std::vector<mc::Interface*> v );

	};

}

#endif
