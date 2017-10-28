#include <iostream>
#include <string>

#include "slider.hpp"
#include "broadcaster.hpp"
#include "datastore.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

#define _max(V) (*std::max_element(V.begin(),V.end()))
#define _min(V) (*std::min_element(V.begin(),V.end()))

#define _try(X) (try { X; } catch (...) {})

namespace mc {
	/* -------------------------------------------------------------------------
		Slider */

	Slider::Slider(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::Scale(cobject),
		blocked (false),
		glade_ref(refGlade),
		scaler(nullptr)
	{
	}

	Slider::~Slider(){
		start_ref.clear();
		end_ref.clear();
	}

	void Slider::notify( Event* e ){
		if (e) {
			switch(e->type()){
				case Event::Type::SINGLE:
					if(_in(e->sender(),start_ref)||_in(e->sender(),end_ref)||e->sender()==scaler){
						populate();
					}
					break;
				case Event::Type::ALL:
					break;
			}
		}
	}

	void Slider::on_value_changed(){
		broadcaster->broadcast(Event(this));
		Gtk::Scale::on_value_changed();
	}

	void Slider::set_marks(){
		if(!marks.empty()){
			for(auto& mark : marks){
				this->add_mark(mark.first,Gtk::POS_BOTTOM,mark.second);
			}
		}
	}

	void Slider::set_marks( std::map<double,std::string> m ){
		marks = m;
		set_marks();
	}

	void Slider::set_scaler( mc::Interface* i ){
		scaler = i;
	}

	void Slider::set_references( std::vector<mc::Interface*> s, std::vector<mc::Interface*> e ){
		start_ref = s;
		end_ref = e;
		populate();
	}

	void Slider::set_columns( std::vector<std::string> c ){
		columns = c;
	}

	void Slider::populate(){
		if(!start_ref.empty() && !end_ref.empty()){

			Records start_r = data->get( start_ref, columns );
			Records end_r   = data->get( end_ref, columns );

			if(start_r.size()>0 && end_r.size()>0){
				std::vector<double> start_vals;
				std::vector<double> end_vals;

				for(auto& i : start_r[0]){
					start_vals.push_back( std::stod(i) );
				}

				for(auto& i : end_r[0]){
					end_vals.push_back( std::stod(i) );
				}

				double s_max = _max(start_vals);
				double s_min = _min(start_vals);
				double e_max = _max(end_vals);
				double e_min = _min(end_vals);

				double scale = scaler ? std::stod(scaler->get_value())/100 : 1.0;

				double tmin = s_min < e_min ? s_min : e_min;
				double tmax = s_max < e_max ? s_max : e_max;

				double min, max, mid;
				if(tmin!=tmax){
					min = (fabs(s_min-e_min)*scale) + tmin;
					max = (fabs(s_max-e_max)*scale) + tmax;

					mid = (max-min)/2+min;
					set_value( min, max, mid );
					unfix();
				}
				else {
					set_value(tmax-1,tmax+1,tmax);
					fix();
				}

			}
		}
	}

	void Slider::block( bool b ){
		blocked = b;
	}

	std::string Slider::get_value(){
		return std::to_string(Gtk::Scale::get_value());
	}

	void Slider::fix(){
		gtk_widget_set_sensitive ((GtkWidget*)(this->gobj()), false);
	}

	void Slider::unfix(){
		gtk_widget_set_sensitive ((GtkWidget*)(this->gobj()), true);
	}

	void Slider::set_value( double min, double max, double mid ){
		block(true);
		Gtk::Scale::set_range(min,max);
		Gtk::Scale::set_value(mid);
		Gtk::Scale::clear_marks();
		Gtk::Scale::add_mark(mid,Gtk::POS_BOTTOM,"default");
		set_marks();
		block(false);
		broadcaster->broadcast(Event(Event::Type::ALL,this));
	}

	void Slider::set_value( std::string s ){
		try {
			double v = std::stod(s);
			this->set_value(v-1,v+1,v);
		} catch (...){

		}
	}

}
