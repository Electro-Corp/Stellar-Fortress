/*
  STELLAR FORTRESS - GRAPHICS ENGINE
  SCREEN_H

  Authors:
  Electro_Corp;
*/
#ifndef SCREEN_H
#define SCREEN_H
#include "window.h"
#include <vector>
#include <ncurses.h>

#include "../other/log.h"
class Screen{
private:
  std::vector<Window*> windows;
  MEVENT event;
  Logger l;
public:
  Screen(){
    // mask all mouse inputs that we want
    mousemask(BUTTON1_CLICKED, NULL);
   // l = Logger("screen1");
  }
  void addWindow(Window* window){
    this->windows.push_back(window);
  }
  /*
  */
  void updateMouseInput(){
    
    
    int ch = getch();
    
    if(ch == KEY_MOUSE){
      if(getmouse(&event) == OK){
          // send mouse input to the window in which it happpend 
          int mouseX = event.x;
          int mouseY = event.y;
          for(int i = 0; i < windows.size(); i++){

            if((windows[i]->x < mouseX && (windows[i]->x + windows[i]->width > mouseX)) &&
               (windows[i]->y < mouseY && (windows[i]->y + windows[i]->height > mouseY))
              ){
                // send that window relative coordinates for the input
                windows[i]->MouseEvent(mouseX, mouseY);
              }
          }
      }
    }
    
  }
};
#endif