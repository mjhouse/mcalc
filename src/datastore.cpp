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

	std::vector<std::vector<std::string>> DataStore::query( std::string q ) {
		sqlite3_stmt *statement;
		std::vector<std::vector<std::string>> results;

		if (this->open()){
			if(sqlite3_prepare_v2(database, q.c_str(), -1, &statement, NULL) == SQLITE_OK){

				while (true) {
					if ( sqlite3_step(statement) == SQLITE_ROW ) {
						std::vector<std::string> values;
						for(int i = 0; i < sqlite3_column_count(statement); i++){
							std::string value = (char*)sqlite3_column_text(statement,i);
							values.push_back(value);
						}
						results.push_back(values);
					} else {
						break;
					}
				}

			} else {
				_print(sqlite3_errmsg(database));
			}
		}

		sqlite3_finalize(statement);
		this->close();
		return results;
	}

	// ----------------------------------------------
	// Public Functions
	std::vector<std::string> DataStore::material( std::map<std::string,std::string> ref ){
		if(ref.size()<=5){
			std::string req = "SELECT max_feed, min_feed, max_sfpm, min_sfpm FROM materials WHERE ";
			for (std::map<std::string,std::string>::iterator it = ref.begin(); it != ref.end(); it++) {
				req += it->first + " = '" + it->second + "'";
				if(std::next(it)!=ref.end()){
					req += " AND ";
				} else {
					req += " LIMIT 1;";
				}
			}

			std::vector<std::vector<std::string>> r = this->query(req);
			if(r.size()>0){
				return r[0];
			} else {
				return std::vector<std::string>{};
			}
		}
	}

}
