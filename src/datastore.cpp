#include "datastore.hpp"
#include "interface.hpp"
#include "data.hpp"
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	DataStore::DataStore() : data(static_data::DATA) {}

	DataStore::~DataStore(){}

	DataStore* DataStore::get_instance(){
		static DataStore datastore;
		return &datastore;
	}

	// --------------------------------------------
	// Functions
	json DataStore::get_value( std::vector<Interface*> p ){
		try {
			json k = data;
			for(auto& a : p){
				k = k[a->get_value()];
			}
			return k;
		}
		catch (json::exception const& err) {
			return json::array();
		}
	}

}
