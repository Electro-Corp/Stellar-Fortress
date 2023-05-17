// small enough that it can be in just a header
#include "../utils/color.h"
class Tile{
  public:
  int x,y;
  Color color;
  bool isOccupied = false;
  Tile(Color color, int x, int y, bool isO){
    this->color = color;
    this->x = x;
    this->y = y;
    this->isOccupied = isO;
  }
}