

#include "datastore.hpp"
#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	Entry::Entry() {
		this->value = "";
		this->_type = EntryType::STRING;
	};

	Entry::Entry( int i ) {
		this->value = std::to_string(i);
		this->_type = EntryType::INTEGER;
	};

	Entry::Entry( float f ) {
		this->value = std::to_string(f);
		this->_type = EntryType::FLOAT;
	};

	Entry::Entry( std::string s ) {
		this->value = s;
		this->_type = EntryType::STRING;
	};

	void Entry::set( std::string s ){
		this->value = s;
		this->_type = EntryType::STRING;
	};

	void Entry::set( int i ){
		this->value = i;
		this->_type = EntryType::INTEGER;
	};

	void Entry::set( float f ){
		this->value = f;
		this->_type = EntryType::FLOAT;
	};

	std::string Entry::get_str(){
		return this->value;
	};

	int Entry::get_int(){
		try {
			return std::stoi(this->value);
		} catch (std::invalid_argument &e) {
			return 0;
		}
	};

	float Entry::get_float(){
		try {
			return std::stof(this->value);
		} catch (std::invalid_argument &e) {
			return 0.0f;
		}
	};

	EntryType Entry::type() {
		return this->_type;
	};

	std::string Entry::type_str() {
		switch (this->_type){
			case EntryType::STRING: return "STRING";
			case EntryType::INTEGER: return "INTEGER";
			case EntryType::FLOAT: return "FLOAT";
		};
	};

	std::string Entry::to_string() {
		std::string r = "E: " + this->type_str() + " " + this->get_str();
		return r;
	}

	/* -------------------------------------------------------------------------
		TABLE */
	Table::Table( int r, int c ){
		this->cells.resize( c, std::vector<Entry>( r , Entry() ) );
	};

	Table::~Table(){};

	Entry* Table::get( int r, int c ) {
		return &(cells.at(r).at(c));
	}

	void Table::print(){
		for(int i = 0; i < cells.size(); i++){
			std::vector<Entry> entries = cells.at(i);
			for(int j = 0; j < entries.size(); j++){
				Entry e = entries.at(j);
				std::string c = "("+std::to_string(i)+","+std::to_string(j)+") ";
				std::cout << c << e.to_string() << ", ";
			}
			std::cout << std::endl;
		}
	}
}
