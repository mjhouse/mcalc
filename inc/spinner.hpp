/** @file

	@brief		The class definition file for the spinner
				class.

	@details 	Acts as a wrapper for a Gtk::SpinButton, updates
				the state and broadcasts change events.

	@author Michael House
	@version 0.1 10/19/17
*/

#ifndef MCALC_SPINNER_HPP
#define MCALC_SPINNER_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

namespace mc {

	class Event;

	/**
		A wrapper around a Gtk::Spinbutton.
	*/
	class Spinner : public Interface {
		private:
			json* data;
			sigc::connection on_change_conn;
			std::vector<Interface*> references;
			Gtk::SpinButton* widget;

		public:
			/**
				Constructor
				@param w the Gtk::SpinButton to wrap
				@param d Pointer to the json datastore
			*/
			Spinner( Gtk::SpinButton* w, json* d);

			/** Destructor */
			~Spinner();

			/**
				Update the Interface about change
				events. Used by broadcaster.
				@param e The event object
			*/
			void notify(Event* e);

			/**
				Generates a change event and
				sends it to Broadcaster.
			*/
			void broadcast();

			/**
				Add references to the interface that will trigger
				the Spinner to update when they change.
				@param r A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<Interface*> r );

			/**
				Returns a string representation of the current
				value of the Spinner.
			*/
			std::string get_value();

			/**
				Sets the current value of the Spinner..
			*/
			void set_value( double d );
	};
}

#endif
