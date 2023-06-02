#ifndef PLANET_H
#define PLANET_H

#include "../../map_generation/planetmap.h"
#include "./terraintypes/terraintype.h"

class Planet{
public:
  //char* resources[];
  //char* colors[];
  
	Planet(std::string, int);
  int init();
	void reduceFood();
  PlanetMap* get_map();
	// Buildings
	void addBuilding();
  void generate_terrain_types();
  PlanetMap* pMap;

  private:
    int size;
    std::vector<TerrainType> regions;
    
};

#include "planet.cpp"
#endif
