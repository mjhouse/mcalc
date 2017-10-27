#include "datastore.hpp"
#include "filechooserbutton.hpp"
#include "broadcaster.hpp"

namespace mc {

	/* -------------------------------------------------------------------------
		FileChooserButton */
	FileChooserButton::FileChooserButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:	Gtk::FileChooserButton(cobject),
		glade_ref(refGlade)
	{

	}

	FileChooserButton::~FileChooserButton(){}

	void FileChooserButton::notify( Event* /* e */){}

	std::string FileChooserButton::get_value(){
		return this->get_filename();
	}

}
