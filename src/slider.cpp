#include "slider.hpp"
#include "broadcaster.hpp"

#define _in(E,V) (std::find(V.begin(), V.end(), E) != V.end())

#define _max(V) (*std::max_element(V.begin(),V.end()))
#define _min(V) (*std::min_element(V.begin(),V.end()))

namespace mc {

	/* -------------------------------------------------------------------------
		Slider */
	Slider::Slider( Gtk::Scale* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_value_changed().connect(sigc::mem_fun(*this,
			&Slider::broadcast));
	};

	Slider::~Slider(){};

	void Slider::notify( Event* e ){
		switch(e->type()){
			case Event::Type::SINGLE:
				if(_in(e->sender(),start_ref)||_in(e->sender(),end_ref)||e->sender()==scaler){
					populate();
				}
				break;
			case Event::Type::ALL:
				break;
		}
	};

	void Slider::broadcast(){
		broadcaster->broadcast(new Event(this));
	};

	void Slider::set_marks(){
		if(!marks.empty()){
			for(auto& mark : marks){
				widget->add_mark(mark.first,Gtk::POS_BOTTOM,mark.second);
			}
		}
	};

	void Slider::set_marks( std::map<double,std::string> m ){
		marks = m;
		set_marks();
	};

	void Slider::set_scaler( Interface* i ){
		scaler = i;
	};

	void Slider::set_references( std::vector<Interface*> s, std::vector<Interface*> e ){
		start_ref = s;
		end_ref = e;
		populate();
	};

	void Slider::populate(){
		if(!start_ref.empty() && !end_ref.empty()){
			std::vector<double> vstart = as_vector( tunnel(data,start_ref) );
			std::vector<double> vend = as_vector(tunnel(data,end_ref));

			double s_max = _max(vstart);
			double s_min = _min(vstart);
			double e_max = _max(vend);
			double e_min = _min(vend);
			double scale = scaler ? std::stod(scaler->get_value())/100 : 1.0;

			double tmin = s_min < e_min ? s_min : e_min;
			double tmax = s_max < e_max ? s_max : e_max;

			double min = (fabs(s_min-e_min)*scale) + tmin;
			double max = (fabs(s_max-e_max)*scale) + tmax;

			double mid = (max-min)/2+min;
			set_value( min, max, mid );
		}
	};

	std::string Slider::get_value(){
		return std::to_string(widget->get_value());
	};

	void Slider::set_value( double min, double max, double mid ){
		on_change_conn.block(true);
		widget->set_range(min,max);
		widget->set_value(mid);
		widget->clear_marks();
		widget->add_mark(mid,Gtk::POS_BOTTOM,"default");
		set_marks();
		on_change_conn.block(false);
		broadcaster->broadcast(new Event(Event::Type::ALL,this));
	};

}
