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

/** Nested vectors in vectors are defined as 'Records' */
typedef std::vector<std::vector<std::string>> Records;

/** Inner vectors of 'Records' are 'Record' */
typedef std::vector<std::string> Record;

/** @namespace mc

	The mc namespace exists only to isolate
	the application from dependencies.
*/
namespace mc {

	class Settings;
	class Interface;

	/**
		This is the main source of all data
		used by the application. It contains
		tables of values that are used to populate
		the UI and perform calculations.
	*/
	class DataStore {
		private:
			sqlite3 *database;
			std::string path;
			DataStore( std::string p );

			bool open();
			void close();

			std::vector<std::vector<std::string>> query_vector( std::string q );
			std::vector< std::map<std::string,std::string> > query_map( std::string q );

		public:
			/** The destructor */
			~DataStore();

			/**
				Get the existing datastore instance or create
				a new datastore and return it.
			*/
			static DataStore* get_instance();

			/**
				Get records from the database using a collection of Interface
				objects to build a query.
				@param r The Interfaces to use as a reference.
				@param cols The columns to return
			*/
			std::vector<std::vector<std::string>> get( std::vector<Interface*> r, std::vector<std::string> cols );

			/**
				Get records from the database using a collection of Interface
				objects to build a query. All columns are returned.
				@param r The Interfaces to use as a reference.
			*/
			std::vector<std::vector<std::string>> get( std::vector<Interface*> r );

			/**
				Update a record matching given key/values with new key/values.
				@param table The table name to search in.
				@param s The keys/values to match against.
				@param v The keys/values to update.
			*/
			void update( std::string table, std::map<std::string,std::string> s, std::map<std::string,std::string> v );

			/**
				Fetch a record from the database.
				@param table The table to search in.
				@param s The key/value pairs to match against.
				@return A vector of vectors of strings (rows from the database).
			*/
			std::vector<std::map<std::string,std::string>> fetch( std::string table, std::map<std::string,std::string> s );

			/**
				Fetch a record from the database.
				@param table The table to search in.
				@param s The key/value pairs to match against.
				@param v The values to fetch.
				@return A vector of vectors of strings (rows from the database).
			*/
			std::vector<std::map<std::string,std::string>> fetch( std::string table, std::map<std::string,std::string> s, std::vector<std::string> v );
	};

}

#endif
