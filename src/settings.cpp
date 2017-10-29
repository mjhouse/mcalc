#include "settings.hpp"
#include "datastore.hpp"
#include "broadcaster.hpp"
#include "filechooserbutton.hpp"

namespace mc {

	Settings::Settings() : 	builder(nullptr),
							submit(nullptr),
							data(DataStore::get_instance()),
							broadcaster(Broadcaster::get_instance()),
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

	Settings* Settings::get_instance(){
		static Settings instance;
		return &instance;
	}

	void Settings::set_builder( Glib::RefPtr<Gtk::Builder> b ){
		builder = b;

		FileChooserButton* btn = nullptr;
		builder->get_widget_derived("s_theme_chooser",btn);
		this->bind("theme",btn);
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
		settings.insert(std::pair<Interface*,std::string>(i,s));
	}

	void Settings::save(){
		data->save( this );
	}

	std::map<std::string,std::string> Settings::get_values(){
		std::map<std::string,std::string> vals;
		std::map<Interface*,std::string>::iterator it;
		for(it = settings.begin(); it != settings.end(); it++){
			vals.insert( std::pair<std::string,std::string>( it->second, it->first->get_value() ) );
		}
		return vals;
	}

	void Settings::set_values( std::map<std::string,std::string> v ){
		
	}

	void Settings::notify(Event* /* e */){}

}
