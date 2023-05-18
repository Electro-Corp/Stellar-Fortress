#ifndef TILE_H
#define TILE_H
// small enough that it can be in just a header
#include "../utils/rgb.h"
class Tile {
  public:
  int x,y;
  RGB rgb;
  bool isOccupied = false;
  Tile(RGB color, int x, int y, bool isO){
    this->rgb = color;
    this->x = x;
    this->y = y;
    this->isOccupied = isO;
  }
};
#endif