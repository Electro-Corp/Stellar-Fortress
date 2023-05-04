#ifndef BUILDING_H
#define BUILDING_H
class Building{
public:
  int width, height, x, y;
  int r,g,b;
  Building(int width, int height, int x, int y);
  void setColor(int r, int g, int b);
  
};
#include "building.cpp"
#endif