#ifndef PLANET_H
#define PLANET_H

#include "../../map_generation/planetmap.h"
#include "./terraintypes/terraintype.h"
#include "../utils/readJson.h"

class Planet{
public:
  //char* resources[];
  //char* colors[];
  
	Planet(std::string dir);
  int init();
	void reduceFood();
  PlanetMap* get_map();
	// Buildings
	void addBuilding();
  void generate_terrain_types();
  PlanetMap pMap;
  int sizex;
  int sizey;

  private:
    std::string name;
    std::vector<TerrainType> regions;
    
};

#include "planet.cpp"
#endif
