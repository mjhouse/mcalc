#include "datastore.hpp"
#include "interface.hpp"

#include <vector>
#include <string.h>

#define _print(X) (std::cout << X << std::endl)

namespace mc {

	DataStore::DataStore( std::string p ) : database(NULL), path(p) {}

	DataStore::~DataStore(){}

	DataStore* DataStore::get_instance(){
		static DataStore datastore = DataStore("file:bin/mcalc.db");
		return &datastore;
	}

	// ----------------------------------------------
	// Private Functions
	bool DataStore::open() {
		if (sqlite3_open_v2(path.c_str(), &database,SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI,NULL) == SQLITE_OK)
			return true;

		_print(sqlite3_errmsg(database));
		return false;
	}

	void DataStore::close() {
		sqlite3_close(database);
	}

	Records DataStore::query( std::string q ) {
		sqlite3_stmt *statement;
		Records results;

		if (this->open()){
			if(sqlite3_prepare_v2(database, q.c_str(), -1, &statement, NULL) == SQLITE_OK){

				while (true) {
					if ( sqlite3_step(statement) == SQLITE_ROW ) {
						Record row;
						for(int i = 0; i < sqlite3_column_count(statement); i++){
							std::string value = (char*)sqlite3_column_text(statement,i);
							row.push_back(value);
						}
						results.push_back(row);
					} else {
						break;
					}
				}

			} else {
				_print(q);
				_print(sqlite3_errmsg(database));
			}
		}

		sqlite3_finalize(statement);
		this->close();
		return results;
	}

	// ----------------------------------------------
	// Public Functions

	Records DataStore::get( std::vector<Interface*> r, std::vector<std::string> cols ){
		std::string request = "SELECT ";

		for (std::vector<std::string>::iterator it = cols.begin(); it != cols.end(); it++) {
			request += (std::next(it) != cols.end()) ? *it + ", " : *it;
		}

		request += " FROM materials WHERE ";

		for (std::vector<Interface*>::iterator it = r.begin(); it != r.end(); it++) {
			Interface* tmp = *it;
			if(std::next(it) != r.end()){
				request += tmp->get_column() + "='" + tmp->get_value() + "' AND ";
			} else {
				request += tmp->get_column() + "='" + tmp->get_value() + "'";
			}
		}

		return this->query(request);
	}

	Records DataStore::get( std::vector<Interface*> r ){
		return this->get( r, std::vector<std::string> {"*"});
	}

}
