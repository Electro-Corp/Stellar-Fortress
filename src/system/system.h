#ifndef SYSTEM_H
#define SYSTEM_H
#include "planet/planet.h"
#include <vector>
class System{
private:
	std::vector<Planet> planets;  
  int currentPlanetIndex = 0;
public:
	System(); 
  void SystemTick();
};
#endif