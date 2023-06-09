/*
  TILE_H
  Authors:
      * Electro_Corp
      * Anduwu1
*/
#ifndef TILE_H
#define TILE_H
#include "../utils/rgb.h"
class Tile {
  public:
  int x,y;
  RGB rgb;
  bool isOccupied = false;
  std::string type;

  double height;
  Tile(RGB color, int x, int y, bool isO, double h){
    this->rgb = color;
    this->x = x;
    this->y = y;
    this->isOccupied = isO;
    this->height = h;
  }

  Tile(RGB color, int x, int y, double h, std::string t){
    this->rgb = color;
    this->x = x;
    this->y = y;
    this->isOccupied = false;
    this-> height = h;
    this->type = t;
  }
};
#endif