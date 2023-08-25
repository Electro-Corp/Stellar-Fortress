#ifndef SYSTEM_H
#define SYSTEM_H
#include "planet/planet.h"
#include "utils/readJson.h"
#include <vector>
class System{
private:
	std::vector<Planet> planets;  
  int currentPlanetIndex = 0;
public:
	System(std::string loadFromFile); 
  void SystemTick();
  Planet get_planet(int);
};


#include "system.cpp"
#endif