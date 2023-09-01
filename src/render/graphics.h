/*
  Header file for the graphics system of
  Stellar Fortress

  Uses SFML
*/
#ifndef GRAPHICS_H
#define GRAPHCIS_H
#include <SDL2/SDL.h>
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
class Renderer{
private:
SDL_Window* window;
SDL_Surface* surface;
renderMode rm;

// Menu

public:
  Renderer(int width, int height, renderMode rm);

// Menu Rendering
  

  void procEvents();

  void display();
};
#include "graphics.cpp"
#endif