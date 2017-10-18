#include "mclib.hpp"
#include "interface.hpp"
#include "broadcaster.hpp"

namespace mc {

	/* -------------------------------------------------------------------------
		ComboBoxText */
	ComboBoxText::ComboBoxText( Gtk::ComboBoxText* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_changed().connect(sigc::mem_fun(*this,
			&ComboBoxText::broadcast));
	};

	ComboBoxText::~ComboBoxText(){};

	void ComboBoxText::notify( Interface* s ){
		if(_IN(s,references)) {
			populate();
		}
	};

	void ComboBoxText::broadcast(){
		broadcaster->broadcast(this);
	};

	void ComboBoxText::populate(){
		if(!references.empty()){
			std::vector<std::string> v;
			for(auto& a : references){
				v.push_back(a->get_value());
			}
			this->set_value(v);
		}
	};

	void ComboBoxText::set_references( std::vector<Interface*> i ){
		references = i;
		populate();
	};

	std::string ComboBoxText::get_value(){
		return widget->get_active_text();
	};

	void ComboBoxText::set_value( std::vector<std::string> v ){
		on_change_conn.block(true);
		gtk_combo_box_text_remove_all(widget->gobj());
		json d = *data;

		for(auto& str : v){ d = d[str]; }
		for(json::iterator it = d.begin(); it != d.end(); ++it){
			if (!(*it).is_primitive()) {
				widget->append(it.key());
			} else {
				if (it->type() != json::value_t::null){
					widget->append(it->get<std::string>());
				}
			}
		}
		widget->set_active(0);
		on_change_conn.block(false);
	};
	/* ---------------------------------------------------------------------- */

	/* -------------------------------------------------------------------------
		Slider */
	Slider::Slider( Gtk::Scale* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_value_changed().connect(sigc::mem_fun(*this,
			&Slider::broadcast));
	};

	Slider::~Slider(){};

	void Slider::notify( Interface* s ){
		if(_IN(s,start_ref)||_IN(s,end_ref)||s==scaler){
			populate();
		}
	};

	void Slider::broadcast(){
		broadcaster->broadcast(this);
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
	};
	/* ---------------------------------------------------------------------- */

	Output::Output( Gtk::Label* w, json* d){
		widget = w;
		data = d;
	};

	Output::~Output(){};

	void Output::notify(Interface* s){
		if(_IN(s,references)){
			double result = calculator(references);
			set_value(result);
		}
	};

	void Output::broadcast(){
		broadcaster->broadcast(this);
	};

	void Output::set_references( std::vector<Interface*> r ){
		references = r;
	};

	void Output::set_calculator( std::function<double(std::vector<mc::Interface*>)> f ){
		calculator = f;
	};

	std::string Output::get_value(){
		return widget->get_text();
	};

	void Output::set_value( double v ){
		widget->set_text(std::to_string(v));
	};


	Spinner::Spinner( Gtk::SpinButton* w, json* d){
		widget = w;
		data = d;

		on_change_conn = w->signal_value_changed().connect(sigc::mem_fun(*this,
			&Spinner::broadcast));
	};

	Spinner::~Spinner(){};

	void Spinner::notify(Interface* s){};

	void Spinner::broadcast(){
		broadcaster->broadcast(this);
	};

	void Spinner::set_references( std::vector<Interface*> r ){
		references = r;
	};

	std::string Spinner::get_value(){
		return std::to_string(widget->get_value());
	};

	void Spinner::set_value( double d ){
		widget->set_value(d);
	};
}
