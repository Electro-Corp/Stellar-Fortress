#include "window.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <random>

Window::Window(char* title, int width, int height, int x, int y, Planet* p){
  this->title = title;
  this->width = width;
  this->height = height;
  this->x = x;
  this->y = y;
  this->curPlanet = p;
}



void Window::addObject(Building b){
  this->buildings.push_back(b);
}
//
/*
  WINDOW::RENDERSCREEN
  Render map view of terrain/buildings/Entities 
*/
void Window::RenderScreen(){
  char blank = ' ';
  int* color[]
  int r = 199, g = 63, b = 0;
  // for random colors
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(1,15);
  printf("\033[48;2;0;0;0m");
  // Print Title of window
  printf("\033[%d;%dH",this->y - 1, this->x);
  printf("%s",this->title);
  for(int yDraw = this->y; yDraw < this->height + this->y; yDraw++){
    for(int xDraw = this->x; xDraw < this->width + this->x; xDraw++){
      printf("\033[%d;%dH",yDraw, xDraw);
      printf("\033[48;2;%d;%d;%dm %c  \033[48;2;0;0;0m",r+dist6(rng),g+dist6(rng),b+dist6(rng),blank);
    }
  }
  // Render buildings 
  for(int i = 0; i < buildings.size(); i++){
    for(int yDraw = buildings[i].y + y; yDraw < buildings[i].y + buildings[i].height + y; yDraw++){
      for(int xDraw = buildings[i].x + x; xDraw < buildings[i].x + buildings[i].width + x; xDraw++){
        printf("\033[%d;%dH", yDraw, xDraw);
        printf("\033[48;2;%d;%d;%dm ",buildings[i].r,buildings[i].g,buildings[i].b);
      }
    }
    
  }
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

char* Window::GetInput(char* prompt){
  //this->RenderScreen();
  printf("\033[48;2;0;0;0m");
  printf("\033[%d;%dH",height+y, x);
  printf("%s: ",prompt);
  char* r;
  scanf("%s",r);
  return r;
}