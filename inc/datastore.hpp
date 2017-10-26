/** @file

	@brief		Contains generated data used by MCalc.

	@details 	The DataStore acts as a wrapper around the
				database, performing lookups and saving state.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_DATASTORE_HPP
#define MCALC_DATASTORE_HPP

#include <vector>
#include <map>

extern "C" {
	#include "sqlite3.h"
}

/** @namespace mc

	The mc namespace exists only to isolate
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
		public:
			sqlite3 *database;
			std::string path;
			DataStore( std::string p );

			bool open();
			void close();

			std::vector<std::vector<std::string>> query( std::string q );

		public:
			/** The destructor */
			~DataStore();

			/**
				Get the existing datastore instance or create
				a new datastore and return it.
			*/
			static DataStore* get_instance();

			std::vector<std::string> material( std::map<std::string,std::string> ref );

	};

}

#endif
