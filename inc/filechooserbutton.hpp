/** @file

	@brief		The class definition file for the
				filechooserbutton class.

	@details 	Acts as a wrapper for a Gtk::FileChooserButton,
				broadcasting state changes and updating
				data in the ui.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_FILECHOOSERBUTTON_HPP
#define MCALC_FILECHOOSERBUTTON_HPP

#include <vector>
#include <gtkmm.h>

#include "interface.hpp"

namespace mc {

	class Event;

	/**
		FileChooserButton wraps a Gtk::FileChooserButton,
		allowing it to be treated as an Interface.
	*/
	class FileChooserButton : public mc::Interface, public Gtk::FileChooserButton {
		private:
			const Glib::RefPtr<Gtk::Builder>& glade_ref;

		public:
			/**
				Constructor for the Gtk::Builder
				@param cobject A base object typedef
				@param refGlade A reference to the builder.
			*/
			FileChooserButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

			/** The destructor */
			~FileChooserButton();

			/**
				Method used to update the FileChooserButton by the broadcaster.
				@param e Event received from broadcaster
			*/
			void notify(Event* e);

			/**
				Get the current value of the FileChooserButton
			*/
			std::string get_value();

	};

}

#endif
