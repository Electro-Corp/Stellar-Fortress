/*
  Header file for the graphics system of
  Stellar Fortress

  Uses SDL2 (Very cool)
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
// /#include<SDL2/SDL_image.h>
#include "../system/planet/tile.h"

/*
  Rendering modes:
    * Menu
    * Loading Screen
    * In-Game
*/
enum renderMode{
  RM_Menu = 0,
  RM_LoadScreen = 1,
  RM_Game = 2
};
void bubbleSortButton(std::vector<Button>* MENU_buttons);
class Renderer{
private:
SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer *renderer;
renderMode rm;
int width, height;
// Menu
SDL_Surface *logo;
SDL_Surface *background;
std::vector<Button> MENU_buttons;
public:
  Renderer(int width, int height, renderMode rm);

// Menu Rendering
  void initMenu(std::string logoPath, std::string bgPath);
  void addButton(Button b);
// Loading
  void initLoadScreen(std::string bgPath);

  void procEvents();

  void display(/*std::vector<std::vector<Tile>> tiles = NULL*/);

  // Kill renderer
  void endWindow();
};
#include "graphics.cpp"
#endif