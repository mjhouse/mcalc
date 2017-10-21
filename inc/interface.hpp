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

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/

/** A macro to simplify the creation of a DummyInterface */
#define _vinterface(V) (new mc::DummyInterface(V))

namespace mc {

	class Broadcaster;
	class DummyInterface;
	class Event;

	/**
		The abstract base class for Sliders, ComboBoxText
		etc.
	*/
	class Interface {
		protected:

			/**
				A utility function that will return json for a given
				path of Interfaces. Uses the current value of each one.
				@param d The json to search
				@param i The Interface list to use as a path
			*/
			inline json tunnel(json* d, std::vector<Interface*> i){
				json k = *d;
				for(auto& a : i){k = k[a->get_value()];}
				return k;
			}

			/**
				A utility function that generates a vector of doubles
				from a json array.
				@param d The json array to use
			*/
			inline std::vector<double> as_vector(json d){
				std::vector<double> r;
				if(d.is_array()){
					for(auto& a : d){
						r.push_back(std::stod(a.get<std::string>()));
					}
				}
				return r;
			}


		protected:
			Broadcaster* broadcaster; /**< Pointer to the broadcaster instance */

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
				Update the Interface about change
				events. Used by broadcaster.
				@param e The event object
			*/
			virtual void notify(Event* e)=0;

			/**
				Generates a change event and
				sends it to Broadcaster.
			*/
			virtual void broadcast()=0;
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
			DummyInterface( std::string s ){value=s;};

			/**
				Returns a string representation of the current
				value of the Interface.
			*/
			std::string get_value(){return value;}

			/**
				Update the Interface about change
				events. Used by broadcaster.
				@param e The event object
			*/
			void notify(Event* e){};

			/**
				Generates a change event and
				sends it to Broadcaster.
			*/
			void broadcast(){};
	};
}

#endif
