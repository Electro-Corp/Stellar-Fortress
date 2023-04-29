#include "window.h"
#include <cstdio>

Window::Window(char* title, int width, int height){
  this->title = title;
  this->width = width;
  this->height = height;
}
void Window::addObject(Building b){
  this->buildings.push_back(b);
}
  // Render Functions
void Window::RenderScreen(){
  for(int y = 0; y < this->height; y++){
    for(int x = 0; x < this->width; x++){
     bool found = false;
     for(int i = 0; i < buildings.size(); i++){
       if(x > buildings[i].x && x < buildings[i].width + buildings[i].x && 
        y > buildings[i].y && y < buildings[i].height + buildings[i].y){
         printf("B");
         found = true;
        }
      }
      if(!found)printf("=");
    }
    printf("\n");
  }
}
char* Window::GetInput(char* prompt){
  this->RenderScreen();
  printf("%s: ",prompt);
  char* r;
  scanf("%s",r);
  return r;
}