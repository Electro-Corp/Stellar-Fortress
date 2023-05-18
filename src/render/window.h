#ifndef WINDOW_H
#define WINDOW_H
#include "../system/planet/buildings/building.h"
#include "ui/ui.h"
#include <vector>
#include "../system/planet/planet.h"
#include "../system/planet/entities/human.h"
// Internal game engine componets
#include "../system/planet/tile.h"

class Window {
private:
  int xViewPortMin, xViewPortMax, yViewPortMax, yViewPortMin;
public:
  Planet* curPlanet;
  char* title;
  int width, height, x, y;
  std::vector<Building> buildings;
  std::vector<Human> Humans;
  Window(char* title, int width, int height, int x, int y);
  int getMousePos();
  // Object functions
  void addObject(Building b);
  // Render Functions
  void SetMapViewport(int xViewPortMin, int xViewPortMax, int yViewPortMin, int yViewPortMax);
  void RenderMap(std::vector<std::vector<Tile>> tiles);
  void renderTile(Tile t);
  // For UI
  void RenderPanel(UI* ui);
  char* GetInput(char* prompt);
  char blank = '\0';
};
#include "window.cpp"
#endif
