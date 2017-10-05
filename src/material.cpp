#ifndef MCALC_LATHE_HPP
#define MCALC_LATHE_HPP

#include <iostream>
#include <vector>
#include <gtkmm.h>
#include "json.hpp"
#include "material.hpp"

using json = nlohmann::json;

namespace mcalc {

	namespace lookup {

		static int _major ( std::vector<Material> m ) {
			sort(m.begin(),m.end(), [](Material& a, Material& b){
				return a.get_percentage() > b.get_percentage();
			});
			MaterialType mtype = m[0].get_type();
			return static_cast<int>(mtype);
		};

		static int _minor ( int major, std::vector<Material> m ) {
			
			return 0;
		};

	};

	/* -------------------------------------------------------------------------
		Material */
	Material::Material () : type(MaterialType::none), percentage(0.0) {};

	Material::Material ( MaterialType m, float p ) {
		type = m;
		percentage = p;
	};

	Material::~Material () {};

	void Material::set_type ( MaterialType t ) {
		this->type = t;
	};

	void Material::set_percentage ( float p ) {
		this->percentage = p;
	};

	MaterialType Material::get_type () {
		return this->type;
	};

	float Material::get_percentage () {
		return this->percentage;
	};

	/* -------------------------------------------------------------------------
		Alloy */
	Alloy::Alloy ( float c ) : materials({}) {
		carbon = c;
	};

	Alloy::~Alloy () {};

	bool Alloy::add_material ( MaterialType m, float p ) {
		float total = this->get_percentage() + p;
		if (total<1.0) {
			materials.push_back( Material(m,p) );
			return true;
		} else {
			return false;
		}
	};

	float Alloy::get_percentage () {
		float total = 0.0;
		std::vector<Material>::iterator it;
		for (it = materials.begin(); it != materials.end(); ++it) {
			total += it->get_percentage();
		}
		return total;
	};

	std::string Alloy::designation () {
		int t = lookup::_major(materials);
		std::cout << t << std::endl;

		return "";
	};
}

#endif
