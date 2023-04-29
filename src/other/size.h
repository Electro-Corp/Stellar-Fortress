#include "size.cpp"
#ifndef SIZE_H
#define SIZE_H
class Size {
public:
  int size_x;
  int size_y;

  Size(int x, int y);
  int get_x();
  int get_y();
};
#endif