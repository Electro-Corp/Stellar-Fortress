#ifndef WINDOW_H
#define WINDOW_H
#include "../system/planet/buildings/building.h"
#include "ui/ui.h"
#include <vector>
#include "../system/planet/planet.h"
class Window {
public:
  Planet* curPlanet;
  char* title;
  int width, height, x, y;
  std::vector<Building> buildings;
  Window(char* title, int width, int height, int x, int y);
  int getMousePos();
  // Object functions
  void addObject(Building b);
  // Render Functions
  void RenderScreen();
  // For UI
  void RenderPanel(UI* ui);
  char* GetInput(char* prompt);
  char blank = '\0';
};
#include "window.cpp"
#endif