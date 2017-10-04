#ifndef MCALC_DATASTORE_HPP
#define MCALC_DATASTORE_HPP

#include "json.hpp"
using json = nlohmann::json;

namespace mcalc {

	json get_data(){
		json data = {
			{"fs_mill_data",{
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
			}},
			{"fs_lathe_data",{
				{"velocity",{
					{"Free machining plain carbon steels (resulfurized)",{
						{"Designations",{"1212", "1213", "1215"}},
						{"HSS",{{"low",270},{"high",290}}},
						{"Carbide",{{"low",820},{"high",1045}}}
					}},
					{"Free machining plain carbon steels",{
						{"Designations",{"1108", "1109", "1115", "1117", "1118", "1120", "1126", "1211"}},
						{"HSS",{{"low",215},{"high",235}}},
						{"Carbide",{{"low",950},{"high",950}}}
					}},
					{"Free machining plain carbon steels",{
						{"Designations",{"1132", "1137", "1139", "1140", "1144", "1146", "1151"}},
						{"HSS",{{"low",70},{"high",215}}},
						{"Carbide",{{"low",670},{"high",800}}}
					}},
					{"Free machining plain carbon steels (Leaded)",{
						{"Designations",{"11L17", "11L18", "12L13", "12L14"}},
						{"HSS",{{"low",200},{"high",260}}},
						{"Carbide",{{"low",800},{"high",820}}}
					}},
					{"Plain carbon steels",{
						{"Designations",{"1006", "1008", "1009", "1010", "1012", "1015", "1016", "1017", "1018", "1019", "1020", "1021", "1022", "1023", "1024", "1025", "1026", "1513", "1514"}},
						{"HSS",{{"low",125},{"high",215}}},
						{"Carbide",{{"low",800},{"high",885}}}
					}},
					{"Plain carbon steels",{
						{"Designations",{"1027", "1030", "1033", "1035", "1036", "1037", "1038", "1039", "1040", "1041", "1042", "1043", "1045", "1046", "1048", "1049", "1050", "1052", "1524", "1526", "1527", "1541"}},
						{"HSS",{{"low",55},{"high",180}}},
						{"Carbide",{{"low",670},{"high",970}}}
					}},
					{"Free machining alloy steels (resulfurized):",{
						{"Designations",{"4140", "4150"}},
						{"HSS",{{"low",70},{"high",200}}},
						{"Carbide",{{"low",430},{"high",685}}}
					}},
					{"Water hardening tool steel",{
						{"Designations",{"W1", "W2", "W5"}},
						{"HSS",{{"low",180},{"high",180}}},
						{"Carbide",{{"low",590},{"high",590}}}
					}},
					{"Cold work, oil hardening tool steel",{
						{"Designations",{"O1", "O2", "O6", "O7"}},
						{"HSS",{{"low",125},{"high",125}}},
						{"Carbide",{{"low",590},{"high",590}}}
					}},
					{"Cold work, air hardening tool steel",{
						{"Designations",{"A2", "A3", "A4", "A6", "A7", "A8", "A9", "A10"}},
						{"HSS",{{"low",80},{"high",125}}},
						{"Carbide",{{"low",355},{"high",365}}}
					}},
					{"Stainless steels (Austenitic)",{
						{"Designations",{"201", "202", "301", "302", "304", "304L", "305", "308", "321", "347", "348"}},
						{"HSS",{{"low",115},{"high",135}}},
						{"Carbide",{{"low",570},{"high",570}}}
					}},
					{"Cast Iron",{
						{"Designations",{"ASTM Class 20", "25", "30", "35", "40"}},
						{"HSS",{{"low",145},{"high",215}}},
						{"Carbide",{{"low",410},{"high",410}}}
					}},
					{"Brass",{
						{"Designations",{"C35600", "C37700", "C36000", "C33200", "C34200", "C35300", "C48500", "C34000"}},
						{"HSS",{{"low",300},{"high",350}}},
						{"Carbide",{{"low",1170},{"high",1170}}}
					}},
					{"Bronze",{
						{"Designations",{"C65500", "C22600", "C65100", "C67500"}},
						{"HSS",{{"low",200},{"high",250}}},
						{"Carbide",{{"low",715},{"high",715}}}
					}},
					{"Wrought aluminum",{
						{"Designations",{"6061-T6", "5000", "6000", "7000 series"}},
						{"HSS",{{"low",500},{"high",600}}},
						{"Carbide",{{"low",2820},{"high",2820}}}
					}},
					{"Cast aluminum",{
						{"Designations",{"Sand and permanent mold casting alloys"}},
						{"HSS",{{"low",600},{"high",750}}},
						{"Carbide",{{"low",2820},{"high",2820}}}
					}}
				}},
				{"feedrate",{
					{"SAE 1020 - Low Carbon Steel",{
						{"HSS",{
							{"low",0.002},
							{"high",0.020}
						}},
						{"Carbide",{
							{"low",0.006},
							{"high",0.035}
						}}
					}},
					{"SAE 1050 - High Carbon Steel",{
						{"HSS",{
							{"low",0.002},
							{"high",0.015}
						}},
						{"Carbide",{
							{"low",0.006},
							{"high",0.030}
						}}
					}},
					{"Stainless Steel",{
						{"HSS",{
							{"low",0.002},
							{"high",0.005}
						}},
						{"Carbide",{
							{"low",0.003},
							{"high",0.006}
						}}
					}},
					{"Aluminum",{
						{"HSS",{
							{"low",0.003},
							{"high",0.030}
						}},
						{"Carbide",{
							{"low",0.008},
							{"high",0.045}
						}}
					}},
					{"Brass & Bronze",{
						{"HSS",{
							{"low",0.003},
							{"high",0.025}
						}},
						{"Carbide",{
							{"low",0.008},
							{"high",0.040}
						}}
					}},
					{"Plastics*",{
						{"HSS",{
							{"low",0.005},
							{"high",0.050}
						}},
						{"Carbide",{
							{"low",0.005},
							{"high",0.050}
						}}
					}}
				}
			}}}
		};

		return data;
	};

}

#endif
