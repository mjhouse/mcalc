#include <iostream>
#include <vector>

#include "group.hpp"

namespace mcalc {

	Group::Group( Glib::RefPtr<Gtk::Builder> builder, std::vector<std::string> names ){
		for( const auto &name : names ){
			this->values[name] = "";
			this->widgets[name] = builder->get_widget();
		}
	};

	Group::~Group(){

	};

}
