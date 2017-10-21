/** @file

	@brief		The class definition file for the output
				class.

	@details 	Acts as a wrapper for a Gtk::Label, updates
				the state and calculates output values.

	@author Michael House
	@version 0.1 10/19/17
*/

#ifndef MCALC_OUTPUT_HPP
#define MCALC_OUTPUT_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

namespace mc {

	class Event;

	/**
		The Output class wraps a Gtk::Label in the UI and
		uses a provided lambda function to calculate a display value.
	*/
	class Output : public mc::Interface, public Gtk::Label {
		private:
			bool blocked;
			json* data;
			std::vector<mc::Interface*> references;
			std::function<double(std::vector<mc::Interface*>)> calculator;

		public:
			/**
				Constructor
				@param w the Gtk::Label to wrap
				@param d Pointer to the json datastore
			*/
			Output(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

			/** Destructor */
			~Output();

			/**
				Update the Interface about change
				events. Used by broadcaster.
				@param e The event object
			*/
			void notify(Event* e);

			/**
				Set internal json data
			*/
			void set_data(json* d);

			/**
				Generates a change event and
				sends it to Broadcaster.
			*/
			void broadcast();


			void block( bool b );

			/**
				Add references to the interface that will trigger
				the Output to update when they change.
				@param r A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<mc::Interface*> r );

			/**
				Set the calculating function that will be used to
				generate output given the current state of the
				references.
				@param f A function that will be used to calculate output.
			*/
			void set_calculator( std::function<double(std::vector<mc::Interface*>)> f );

			/**
				Returns a string representation of the current
				value of the Interface.
			*/
			std::string get_value();

			/**
				Sets the value of the output.
				@param v A double value to set in the ui.
			*/
			void set_value( double v );
	};

}

#endif
