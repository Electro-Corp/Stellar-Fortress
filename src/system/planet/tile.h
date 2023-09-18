/*
  TILE_H
  Authors:
      * Electro_Corp
      * Anduwu1
*/
#ifndef TILE_H
#define TILE_H

#include "../utils/rgb.h"
#include "./terraintypes/terraintype.h"
#include "../../map_generation/biomedata.h"
#include <stdexcept>

class Tile {
  public:
  int x,y, b_seed, biome;
  int height, heat, humidity;
  RGB rgb;
  bool isOccupied = false;
  
  Tile() { }
  Tile(int x, int y){
    this->x = x;
    this->y = y;
  }
  
};
#endif