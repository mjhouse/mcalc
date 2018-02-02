#include "datastore.hpp"
#include "interface.hpp"
#include "settings.hpp"

#include <vector>
#include <string.h>

#define _print(X) (std::cout << X << std::endl)

namespace mc {

	DataStore::DataStore( std::string p )
	:	database(NULL),
		path(p)
	{

	}

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

	std::vector<std::vector<std::string>> DataStore::query_vector( std::string q ) {
		sqlite3_stmt *statement;
		std::vector<std::vector<std::string>> results;

		if (this->open()){
			if(sqlite3_prepare_v2(database, q.c_str(), -1, &statement, NULL) == SQLITE_OK){

				while (true) {
					if ( sqlite3_step(statement) == SQLITE_ROW ) {
						std::vector<std::string> row;
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

<<<<<<< HEAD
	std::map<std::string,std::string> DataStore::map_query( std::string q ) {
		sqlite3_stmt *statement;
		std::map<std::string,std::string> results;

		if (this->open() && sqlite3_prepare_v2(database, q.c_str(), -1, &statement, NULL) == SQLITE_OK){
			if ( sqlite3_step(statement) == SQLITE_ROW ){
				for(int i = 0; i < sqlite3_column_count(statement); i++){
					std::string key = sqlite3_column_name(statement,i);
					std::string value = (char*)sqlite3_column_text(statement,i);
					results.insert(std::pair<std::string,std::string>(key,value));
				}
			}
		} else {
				_print(sqlite3_errmsg(database));
=======
	std::vector< std::map<std::string,std::string> > DataStore::query_map( std::string q ) {
		sqlite3_stmt *statement;
		std::vector< std::map<std::string,std::string> > results;

		if (this->open()){
			if(sqlite3_prepare_v2(database, q.c_str(), -1, &statement, NULL) == SQLITE_OK){

				while (true) {
					if ( sqlite3_step(statement) == SQLITE_ROW ) {
						std::map<std::string,std::string> row;
						for(int i = 0; i < sqlite3_column_count(statement); i++){
							std::string key = (char*)sqlite3_column_name(statement,i);
							std::string value = (char*)sqlite3_column_text(statement,i);
							row.insert( std::pair<std::string,std::string>(key,value) );
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
>>>>>>> a579b920af66391f21193620b890c7f47b777937
		}

		sqlite3_finalize(statement);
		this->close();
		return results;
	}

	// ----------------------------------------------
	// Public Functions

	std::vector<std::vector<std::string>> DataStore::get( std::vector<Interface*> r, std::vector<std::string> cols ){
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

		return this->query_vector(request);
	}

	std::vector<std::vector<std::string>> DataStore::get( std::vector<Interface*> r ){
		return this->get( r, std::vector<std::string> {"*"});
	}

	void DataStore::update( std::string table, std::map<std::string,std::string> s, std::map<std::string,std::string> v ){
		std::map<std::string,std::string>::iterator it;
		if (!s.empty() && !v.empty()){
			std::string request = "UPDATE " + table + " SET";

			for(it = v.begin(); it != v.end(); it++){
				request += " " + it->first + " = '" + it->second + "'";
				request += (std::next(it) != v.end()) ? "," : " WHERE";
			}

<<<<<<< HEAD
		for(it = v.begin(); it != v.end(); it++){
			request += " " + it->first + " = '" + it->second + "'";
			request += (std::next(it) != v.end()) ? "," : " WHERE";
		}

		for(it = s.begin(); it != s.end(); it++){
			request += " " + it->first + " = '" + it->second + "'";
			request += (std::next(it) != s.end()) ? "," : ";";
=======
			for(it = s.begin(); it != s.end(); it++){
				request += " " + it->first + " = '" + it->second + "'";
				request += (std::next(it) != s.end()) ? "," : ";";
			}

			this->query_vector(request);
>>>>>>> a579b920af66391f21193620b890c7f47b777937
		}
	}

<<<<<<< HEAD
		sqlite3_stmt* statement;
		if(this->open() && sqlite3_prepare_v2(database, request.c_str(), -1, &statement, NULL) == SQLITE_OK){
			if(sqlite3_step(statement) != SQLITE_DONE){
				_print(sqlite3_errmsg(database));
			};
		} else {
			_print(sqlite3_errmsg(database));
		}

		sqlite3_finalize(statement);
		this->close();
	}

	void DataStore::save( Settings* s ){
		std::map<std::string,std::string> settings = s->get_values();
=======
	std::vector<std::map<std::string,std::string>> DataStore::fetch( std::string table, std::map<std::string,std::string> s ){
		return this->fetch(table,s,std::vector<std::string>{"*"});
	}

	std::vector<std::map<std::string,std::string>> DataStore::fetch( std::string table, std::map<std::string,std::string> s, std::vector<std::string> v ){
		if (!s.empty() && !v.empty()){
			std::string request = "SELECT ";
>>>>>>> a579b920af66391f21193620b890c7f47b777937

			for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++){
				request += " " + *it;
				request += (std::next(it) != v.end()) ? "," : " FROM " + table + " WHERE";
			}

			for(std::map<std::string,std::string>::iterator it = s.begin(); it != s.end(); it++){
				request += " " + it->first + " = '" + it->second + "'";
				request += (std::next(it) != s.end()) ? "," : ";";
			}

			return this->query_map(request);
		} else {
			return std::vector<std::map<std::string,std::string>> {};
		}
	}

	void DataStore::load( std::string p, Settings* s ){
		std::string request = "SELECT * FROM settings WHERE profile = '" + p + "'";
		std::map<std::string,std::string> results = this->map_query(request);
		if(!results.empty()){
			s->set_values( results );
		}
	}

}
