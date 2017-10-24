/** @file

	@brief		The class definition file for the slider
				class.

	@details 	Acts as a wrapper for a Gtk::Scale, updates
				the state and calculates max and min values.

	@author Michael House
	@version 0.1 10/19/17
*/

#ifndef MCALC_SLIDER_HPP
#define MCALC_SLIDER_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

namespace mc {

	class Interface;
	class Event;

	/**
		A Slider wraps a Gtk::Scale widget in the UI and
		manages flexible max/min values, responding to
		broadcast events.
	*/
	class Slider : public mc::Interface, public Gtk::Scale {
		private:
			bool blocked;
			std::vector<mc::Interface*> start_ref;
			std::vector<mc::Interface*> end_ref;
			mc::Interface* scaler;
			std::map<double,std::string> marks;

		public:
			/**
				Constructor for the Gtk::Builder
				@param cobject A base object typedef
				@param refGlade A reference to the builder.
			*/
			Slider(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

			/** Destructor */
			~Slider();

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
			void on_value_changed();

			/**
				Populates the UI with values from the datastore.
			*/
			void populate();


			/**
				Sets any marks that this Slider contains in the UI.
			*/
			void set_marks();

			/**
				Overloaded set_marks is used to provide
				constant mark values to add to the Gtk::Scale.
				@param m A map of double (position) and string (label) values.
			*/
			void set_marks( std::map<double,std::string> m );

			/**
				The scaler is an Interface that is expected to
				be a value between 0-100 and is used to change
				the max and min values of this slider.
				@param i The Interface to use as a scaler.
			*/
			void set_scaler( mc::Interface* i );

			/**
				Add references to the interface that will trigger
				the Slider to update. Slider uses two sets of references
				and a scaler value to move the available range of
				values between the two.

				@param s A vector of Interfaces to use as a reference
				@param e A vector of Interfaces to use as a reference
			*/
			void set_references( std::vector<mc::Interface*> s, std::vector<mc::Interface*> e );

			/**
				Stop/start broadcasting events
				@param b True allows broadcasts, false dis-allows.
			*/
			void block( bool b );

			/**
				Returns a string representation of the current
				value of the Interface.
			*/
			std::string get_value();

			/**
				Freezes the slider at the current value.
			*/
			void fix();

			/**
				Freezes the slider at a constant value.
				@param val The value to set the slider at.
			*/
			void fix( double val );

			/**
				Unfreezes the slider.
			*/
			void unfix();

			/**
				Sets the max, min and current position of the Slider.
			*/
			void set_value( double max, double min, double val );
	};

}

#endif
