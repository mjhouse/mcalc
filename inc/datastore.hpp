#ifndef MCALC_DATASTORE_HPP
#define MCALC_DATASTORE_HPP

#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	enum struct EntryType {
		STRING,
		FLOAT,
		INTEGER,
	};

	class Entry {
		private:
			std::string value;
			EntryType _type;

		public:
			Entry();
			Entry( int i );
			Entry( float i );
			Entry( std::string i );
			~Entry(){};

			void set( std::string s );
			void set( int i );
			void set( float f );

			std::string get_str();
			int get_int();
			float get_float();

			EntryType type();
			std::string type_str();

			std::string to_string();
	};

	class Table {
		private:
			std::map<std::string, int> column_titles;
			std::map<std::string, int> row_titles;
			std::vector<std::vector<Entry>> cells;

		public:
			Table( int r, int c );
			~Table();

			Entry* get( int r, int c );

			void print();
	};

}
#endif
