#include "datastore.hpp"
#include "interface.hpp"

#include <vector>

#define _print(X) (std::cout << X << std::endl)

namespace mc {

	DataStore::DataStore() : database(NULL) {
		if (!open("file:mcalc.db")) {
			_print("database failed");
		} else {
			_print("database open");
		}
	}

	DataStore::~DataStore(){
		sqlite3_close(database);
	}

	DataStore* DataStore::get_instance(){
		static DataStore datastore;
		return &datastore;
	}

	// ----------------------------------------------
	// Private Functions
	bool DataStore::open( std::string f ) {
		if (sqlite3_open_v2(f.c_str(), &database,SQLITE_OPEN_READWRITE,NULL) == SQLITE_OK)
			return true;

		return false;
	}

	void DataStore::query( std::string q ) {
		sqlite3_stmt *statement;

	}

	// ----------------------------------------------
	// Public Functions
	std::string DataStore::lookup( std::map<std::string,std::string> ref, int col ){

	}

}
