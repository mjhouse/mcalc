#ifndef GROUP_HPP
#define GROUP_HPP

#include <gtkmm.h>
#include <string>
#include <map>

namespace mcalc {

	class Group {
		private:
			std::map<std::string,Gtk::Widget*> widgets = {};
			std::map<std::string,std::string> values = {};

		protected:
		public:
			Group(){};
			Group( Glib::RefPtr<Gtk::Builder> b, std::vector<std::string> names );
			~Group();
	};

}

#endif
