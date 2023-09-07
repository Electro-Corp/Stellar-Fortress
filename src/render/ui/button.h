#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
class Button{
public:
  std::string text;
  void (*onClick)();
  int x,y, width, height, yoffset = 30; // shitty hack
  SDL_Surface *buttonSurface;
  Button(std::string text, int x, int y, void (*onClick)(), std::string buttonImagePath){
    this->text;
    this->onClick = onClick;
    this->x = x;
    this->y = y;
    buttonSurface = SDL_LoadBMP(buttonImagePath.c_str());
  }
  void click(){
    onClick();
  }
};
#endif