/** @file

	@brief		The class definition file for the spinner
				class.

	@details 	Acts as a wrapper for a Gtk::SpinButton, updates
				the state and broadcasts change events.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_SPINNER_HPP
#define MCALC_SPINNER_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"


namespace mc {

	class Event;

	/**
		A wrapper around a Gtk::Spinbutton.
	*/
	class Spinner : public mc::Interface, public Gtk::SpinButton {
		private:
			bool blocked;
			const Glib::RefPtr<Gtk::Builder>& glade_ref;
			std::vector<mc::Interface*> references;

		public:
			/**
				Constructor
			*/
			Spinner(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

			/** Destructor */
			~Spinner();

			/**
				Update the Interface about change
				events. Used by broadcaster.
				@param e The event object
			*/
			void notify(Event* e);

			/**
				Sends out a change event.
			*/
			virtual void on_value_changed();

			/**
				Add references to the interface that will trigger
				the Spinner to update when they change.
				@param r A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<mc::Interface*> r );

			/**
				Stop/start broadcasting events
				@param b True allows broadcasts, false dis-allows.
			*/
			void block( bool b );

			/**
				Returns a string representation of the current
				value of the Spinner.
			*/
			std::string get_value();

			/**
				Sets the current value of the Spinner.
			*/
			void set_value( double d );

			/**
				Sets the string value of the Spinner.
			*/
			void set_value( std::string s );
	};
}

#endif
