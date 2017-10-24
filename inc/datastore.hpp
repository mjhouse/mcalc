/** @file

	@brief		Contains generated data used by MCalc.

	@details 	The material JSON object contains a large
				amount of data used by MCalc for lookups
				and calculations. It's generated by a Python
				script.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_DATASTORE_HPP
#define MCALC_DATASTORE_HPP

#include <vector>

#include "json.hpp"
using json = nlohmann::json; /**< alias for the nlohmann namespace*/


/** @namespace mcalc

	The mcalc namespace exists only to isolate
	the application from dependencies.
*/
namespace mc {

	class Interface;

	/**
		This is the main source of all data
		used by the application. It contains
		tables of values that are used to populate
		the UI and perform calculations.
	*/
	class DataStore {
		private:
			json data;
			DataStore();

		public:
			/** The destructor */
			~DataStore();

			/**
				Get the existing datastore instance or create
				a new datastore and return it.
			*/
			static DataStore* get_instance();

			/**
				Get a value from the datastore using a path
				made up of Interface objects.
				@param p collection of Interface objects to use as path.
			*/
			json get_value( std::vector<Interface*> p );

			/**
				Get the first value of the referenced path as a
				double.
				@param p The path to access.
			*/
			double get_first_value( std::vector<Interface*> p );

	};

}

#endif
