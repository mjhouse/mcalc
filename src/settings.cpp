#include "settings.hpp"
#include "datastore.hpp"
#include "broadcaster.hpp"
#include "filechooserbutton.hpp"

namespace mc {

	Settings::Settings() : 	builder(nullptr),
							submit(nullptr),
							data(DataStore::get_instance()),
							broadcaster(Broadcaster::get_instance()),
							profile_name("default"),
							settings({})
	{

			data->load("default",this);
			broadcaster->subscribe(this);
	}

	Settings::~Settings(){
		std::map<Interface*,std::string>::iterator it;
		for(it = settings.begin(); it != settings.end(); it++){
			delete it->first;
			settings.erase(it);
		}
	}

	void Settings::init_components(){
		FileChooserButton* btn = nullptr;

		builder->get_widget_derived("s_theme_chooser",btn);

		this->bind("theme",btn);
	}

	Settings* Settings::get_instance(){
		static Settings instance;
		return &instance;
	}

	void Settings::set_builder( Glib::RefPtr<Gtk::Builder> b ){
		builder = b;
		this->init_components();
	}

	void Settings::set_submit( std::string s ){
		static sigc::connection submit_conn;
		if(builder){
			builder->get_widget(s,submit);

			submit_conn.disconnect();
			submit_conn = submit->signal_clicked().connect(
				sigc::mem_fun(*this,&mc::Settings::save));
		}
	}

	void Settings::bind( std::string s, Interface* i ){
		if (profile_data.find(s) != profile_data.end()) {
			settings.insert(std::pair<Interface*,std::string>(i,s));
		}
	}

	void Settings::load( std::string p ){
		this->profile_name = p;
		std::vector< std::map<std::string,std::string> > vals = data->fetch("settings",std::map<std::string,std::string>{{"profile",p}});
		if(vals.size()>0){
			this->profile_data = vals.at(0);
			for (std::map<Interface*,std::string>::iterator it = settings.begin(); it != settings.end(); it++) {
				Interface* tmp = it->first;
				std::string value = this->profile_data[it->second];
				if(!value.empty()){
					tmp->set_value(value);
				}
			}
		}
	}

	void Settings::save(){
		std::map<std::string,std::string> profile = {{"profile",this->profile_name}};
		data->update( "settings", profile, this->profile_data);
	}

<<<<<<< HEAD
	std::map<std::string,std::string> Settings::get_values(){
		std::map<std::string,std::string> vals;
		std::map<Interface*,std::string>::iterator it;
		for(it = settings.begin(); it != settings.end(); it++){
			vals.insert( std::pair<std::string,std::string>( it->second, it->first->get_value() ) );
=======
	void Settings::notify(Event* e){
		switch(e->type()){
			case Event::Type::SINGLE:
				if (settings.find(e->sender()) != settings.end()){
					std::string key = settings[e->sender()];
					std::string val = (e->sender())->get_value();
					profile_data[key] = val;
				}
				break;
			case Event::Type::ALL:
				break;
>>>>>>> a579b920af66391f21193620b890c7f47b777937
		}
	}

<<<<<<< HEAD
	void Settings::set_values( std::map<std::string,std::string> v ){

	}

	void Settings::notify(Event* /* e */){}

=======
>>>>>>> a579b920af66391f21193620b890c7f47b777937
}
