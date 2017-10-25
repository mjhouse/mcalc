#include "settings.hpp"
#include "interface.hpp"

namespace mc {

	Settings::Settings(){};

	Settings::~Settings(){};

	Settings* Settings::get_instance(){
		static Settings instance;
		return &instance;
	};

	void Settings::set_ui( Glib::RefPtr<Gtk::Builder> b ){
		ui = b;
	};

	void Settings::set_inputs( std::vector<std::string> i ){
		inputs = i;
	};


}
