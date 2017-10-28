/** @file

	@brief		The class definition file for the
				interface abstract base class.

	@details 	Acts as the base class of ComboBoxText,
				Slider, etc.

	@author Michael House
	@version 0.1 10/19/17
*/
#ifndef MCALC_INTERFACE_HPP
#define MCALC_INTERFACE_HPP

#include <vector>
#include <iostream>

/** A macro to simplify the creation of a DummyInterface */
#define _vinterface(V) (new mc::DummyInterface(V))

namespace mc {

	class Broadcaster;
	class DataStore;
	class DummyInterface;
	class Event;

	/**
		The subscriber interface that needs to be implemented
		in order to listen for broadcaster events.
	*/
	class Subscriber {
		protected:
		public:
			/** The constructor. */
			Subscriber(){};

			/** The virtual destructor. */
			virtual ~Subscriber(){};

			/**
				Update the Subscriber about change
				events. Used by broadcaster.
				@param e The event object
			*/
			virtual void notify(Event* e)=0;

	};

	/**
		The abstract base class for Sliders, ComboBoxText
		etc.
	*/
	class Interface : public Subscriber {
		protected:
			Broadcaster* broadcaster; 	/**< Pointer to the broadcaster instance */
			DataStore* data; 			/**< Pointer to the datastore */
			std::string column_name; 	/**< Name of column in database if this Interface refers to one */

		public:
			/** Constructor */
			Interface();

			/** Virtual destructor */
			virtual ~Interface();

			/**
				Returns a string representation of the current
				value of the Interface. Subclass must implement.
			*/
			virtual std::string get_value()=0;

			/**
				Set the value of the Interface.
			*/
			virtual void set_value( std::string s )=0;

			/**
				Set the column that this Interface
				refers to, if the input value of the Interface
				directly maps to the database.
				@param n The column name..
			*/
			void set_column( std::string n );

			/**
				Get the name of the column that this
				Interface refers to, if none is set, get
				empty string.
			*/
			std::string get_column();
	};

	/**
		An empty implementation of Interface that
		wraps a constant string value. Used for
		plugging gaps in a path in the datastore
		when there isn't a UI element for the value.
	*/
	class DummyInterface : public Interface {
		private:
			std::string value;

		public:
			/**
				Constructor sets the value of the
				Interface.
				@param s The constant value to use.
			*/
			DummyInterface( std::string s );

			/**
				Returns a string representation of the current
				value of the Interface.
			*/
			std::string get_value();

			/**
				Sets the current value of the interface.
			*/
			void set_value( std::string s );

			/**
				Set the column name that this input maps to.
				@param n The name of the column
			*/
			void set_column( std::string n );

			/**
				Get the column value.
			*/
			std::string get_column();


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
	};
}

#endif
