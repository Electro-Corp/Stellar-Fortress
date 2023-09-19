#ifndef PLANET_H
#define PLANET_H

#include "../../map_generation/planetmap.h"
#include "./terraintypes/terraintype.h"
#include "../utils/readJson.h"
#include "../utils/rgb.h"
#include "../../map_generation/hhh.h"

class Planet{
public:
  //char* resources[];
  //char* colors[];
  //void reduceFood();


	Planet(std::string dir);
  int init();
  PlanetMap get_map();
	// Buildings
	void addBuilding();
  PlanetMap pMap;
  int sizex;
  int sizey;

  private:
    std::string name;

    std::unordered_map<std::string, int> r_enum;
    std::unordered_map<int, RGB> c_enum;
    std::unordered_map<int, HHH> h_enum;
    
    
};

#include "planet.cpp"
#endif
