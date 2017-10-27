#include "settings.hpp"
#include "datastore.hpp"
#include "broadcaster.hpp"

namespace mc {

	Settings::Settings() : 	data(DataStore::get_instance()),
							broadcaster(Broadcaster::get_instance()),
							settings({})
	{

			broadcaster->subscribe(this);
	}

	Settings::~Settings(){}

	Settings* Settings::get_instance(){
		static Settings instance;
		return &instance;
	}

	void Settings::bind( std::string s, Interface* i ){
		settings.insert(std::pair<Interface*,std::string>(i,s));
	}

	void Settings::save(){
		std::map<Interface*,std::string>::iterator it;
		for(it = settings.begin(); it != settings.end(); it++){
			std::cout << it->second << std::endl;
		}
	}

	void Settings::notify(Event* /* e */){
		//if (settings.find(e->sender()) != settings.end()) {
		//	std::cout << "changed msg setting: " << settings[e->sender()] << std::endl;
		//}
	}

}
