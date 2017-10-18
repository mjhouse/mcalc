#ifndef MCALC_INTERFACE_HPP
#define MCALC_INTERFACE_HPP

#include <vector>
#include "json.hpp"
using json = nlohmann::json;

#define _vinterface(V) (new mc::DummyInterface(V))

namespace mc {

	class Broadcaster;

	class Interface {
		protected:

			// a utility function that will return json for a given
			// path made up of other interface values.
			inline json tunnel(json* d, std::vector<Interface*> i){
				json k = *d;
				for(auto& a : i){k = k[a->get_value()];}
				return k;
			}

			// a utility function that generates a vector of doubles
			// from a json array
			inline std::vector<double> as_vector(json d){
				std::vector<double> r;
				if(d.is_array()){
					for(auto& a : d){
						r.push_back(std::stod(a.get<std::string>()));
					}
				}
				return r;
			}


		protected:
			Broadcaster* broadcaster;

		public:
			Interface();
			~Interface();
			virtual std::string get_value()=0;
			virtual void notify(Interface* s)=0;
			virtual void broadcast()=0;
	};

	class DummyInterface : public Interface {
		private:
			std::string value;
			
		public:
			DummyInterface( std::string s ){value=s;};
			std::string get_value(){return value;}
			void notify(Interface* s){};
			void broadcast(){};
	};
}

#endif
