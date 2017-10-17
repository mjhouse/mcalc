#ifndef MCALC_MCLIB_HPP
#define MCALC_MCLIB_HPP

#include <vector>
#include <iostream>
#include <gtkmm.h>

#include "json.hpp"
using json = nlohmann::json;

namespace mc {

	void set_slider( Gtk::Scale* s, sigc::connection h, json j );
	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d );
	double calculate_rpm ( double v, double d );
}

#endif
