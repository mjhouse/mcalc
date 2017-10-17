#include "mclib.hpp"

namespace mc {

	/* ---------------------------------------------------------------------- */

	void set_slider( Gtk::Scale* s, sigc::connection h, json j ) {
		if (j.is_array()) {
			std::vector<double> v;
			for (json::iterator it = j.begin(); it != j.end(); ++it) {
				std::string val = it->get<std::string>();
				v.push_back(std::stod(val));
			}
			double min = *std::min_element(v.begin(),v.end());
			double max = *std::max_element(v.begin(),v.end());
			double mid = (max-min)/2+min;
			s->set_range(min,max);
			s->set_value(mid);
			s->clear_marks();
			s->add_mark(mid,Gtk::POS_BOTTOM,"default");
		}
	}

	void set_comboboxtext( Gtk::ComboBoxText* c, sigc::connection h, json d ){
		if(d.type() != json::value_t::null){
			h.block(true);
			gtk_combo_box_text_remove_all(c->gobj());
			for (json::iterator it = d.begin(); it != d.end(); ++it) {
				json j = *it;
				if (!j.is_primitive()) {
					c->append(it.key());
				} else {
					if (it->type() != json::value_t::null){
						c->append(it->get<std::string>());
					}
				}
			}
			h.block(false);
			c->set_active(0);
		}
	}

	double calculate_rpm ( double v, double d ) {
		double rpm = (4.0*v)/d;
		if(!std::isinf(rpm)){
			return rpm;
		} else {
			return 0.0;
		}
	};

}
