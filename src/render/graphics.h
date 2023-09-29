/*
  Header file for the graphics system of
  Stellar Fortress

  Uses SDL2 (Very cool)
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "ui/button.h"
#include <SDL2/SDL.h>
#include "SDL_ttf.h"

#include <thread>

//#include <SDL2_image/SDL_image.h>
// /#include<SDL2/SDL_image.h>
#include "../system/planet/tile.h"
#include "../other/log.h"
#include "ui/UIManager.h"
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
int mapXOff, mapYOff;
int viewX, viewY;
int SCALE;
int mouseX, mouseY;
bool mouseDown;
// Menu
SDL_Surface *logo;
SDL_Surface *background;
std::vector<Button> MENU_buttons;
// Load screen
TTF_Font* gFont = NULL; // Font
SDL_Surface* loadTextSurface;
UIManager* uiMan;

// Threads
// Debug
// Logger l;
public:
  Renderer(int width, int height, renderMode rm, std::string* fontPath = nullptr);
  Renderer(int);
  Renderer();

// Menu Rendering
  void initMenu(std::string logoPath, std::string bgPath);
  void addButton(Button b);
// Loading
  void initLoadScreen(std::string bgPath, std::string, bool noBg = false);

// INit ui
  void initUI(UIManager* ui);

// General

  void procEvents();
  Uint32 getTime();

  void display(std::vector<std::vector<Tile>> *tiles = nullptr, bool noLoadImage = false);

  int getMouseX();
  int getMouseY();
  bool isMouseDown();

  // Kill renderer
  void endWindow();
};
#include "graphics.cpp"
#endif