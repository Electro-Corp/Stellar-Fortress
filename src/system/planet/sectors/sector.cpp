#include "sector.h"

//A sector is a square section of the map. Used for pathfinding atm but most likely more later

//CordsPerSector being the size of a sector in this specific planet.
Sector::Sector(int SectorX, int SectorY, int CordsPerSector) {
	this.SecX = SectorX;
  this.SecY = SectorY;
  this.CPS = CordsPerSector;
}

