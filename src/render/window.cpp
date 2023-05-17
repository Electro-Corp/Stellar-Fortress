#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <random>

// Internal game engine componets
#include "../system/planet/tile.h"

Window::Window(char* title, int width, int height, int x, int y){
  this->title = title;
  this->width = width;
  this->height = height;
  this->x = x;
  this->y = y;
}


void Window::RenderMap(std::vector<Tile> tiles, int xViewPortMin, int xViewPortMax, int yViewPortMin, int yViewPortMax){
  // Loser isnt even 
}


// RENDER UI
void Window::RenderPanel(UI* ui){
  printf("\033[48;2;0;0;0m");
  // Print Title of window
  printf("\033[%d;%dH",this->y - 1, this->x);
  printf("%s",this->title);
  for(int yDraw = this->y; yDraw < this->height + this->y; yDraw++){
    for(int xDraw = this->x; xDraw < this->width + this->x; xDraw++){
      printf("\033[%d;%dH",yDraw, xDraw);
      printf("\033[48;2;%d;%d;%dm %c  \033[48;2;0;0;0m",100,100,100,' ');
    }
  }
  for(int i = 0; i < ui->texts.size(); i++){
    printf("\033[%d;%dH",this->y + i + 1, this->x);
    printf("%s",ui->texts[i].text);
  }
}