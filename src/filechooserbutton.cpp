#include "datastore.hpp"
#include "filechooserbutton.hpp"
#include "broadcaster.hpp"

namespace mc {

	/* -------------------------------------------------------------------------
		FileChooserButton */
	FileChooserButton::FileChooserButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::FileChooserButton(cobject),
		glade_ref(refGlade),
		blocked(false)
	{

	}

	FileChooserButton::~FileChooserButton(){}

	void FileChooserButton::on_file_set(){
		if(!blocked){
			broadcaster->broadcast(Event(this));
			Gtk::FileChooserButton::on_file_set();
		}
	}

	void FileChooserButton::notify( Event* /* e */){}

	std::string FileChooserButton::get_value(){
		return this->get_filename();
	}

	void FileChooserButton::set_value( std::string s ){
		this->set_filename(s);
	}

}
