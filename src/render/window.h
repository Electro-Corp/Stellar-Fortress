#ifndef WINDOW_H
#define WINDOW_H
#include "../system/planet/buildings/building.h"
#include <vector>
class Window {
public:
  char* title;
  int width, height;
  std::vector<Building> buildings;
  Window(char* title, int width, int height);

  // Object functions
  void addObject(Building b);
  // Render Functions
  void RenderScreen();
  char* GetInput(char* prompt);
};
#include "window.cpp"

#endif