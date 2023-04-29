#include <iostream>
//#include "other/size.h"
// Systems
#include "system/system.h"
#include "render/window.h"
int main(){
  char* title = "Stellar Dwarfs(just like isaac)";
  //Size size(80, 20);
  Building b(10,10,0,0);
  Window win(title, 80, 20);
  win.addObject(b);
  win.RenderScreen();
  char* i = win.GetInput("Test");
  return 0;
}