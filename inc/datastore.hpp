#ifndef MCALC_DATASTORE_HPP
#define MCALC_DATASTORE_HPP

#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	json get_data(){
		json data = {
			{"fs_materials_data",{
				{"Aluminum-",250.0},
				{"Bakelite-",125.0},
				{"Plastics-",125.0},
				{"Brass and bronze-",250.0},
				{"Bronze, high tensile",85.0},
				{"Cast iron, chilled",35.0},
				{"Cast iron hard",85.0},
				{"Cast iron soft",125.0},
				{"Magnesium",325.0},
				{"Malleable iron",85.0},
				{"Monel, metal",45.0},
				{"Nickel",50.0},
				{"Steel annealed",65.0},
				{"Forged steel",55.0},
				{"Stainless, easy",65.0},
				{"Stainless, hard",35.0},
				{"Tool steel",55.0},
				{"Slate marble and stone",20.0},
				{"Wrought Iron",55.0}
			}}
		};

		return data;
	};

}

#endif
