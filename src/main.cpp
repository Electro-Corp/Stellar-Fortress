#include <iostream>
//#include "other/size.h" (andrew doesnt know much about that)
// Systems
#include "system/system.h"
#include "system/utils/readJson.h" //debug, main.cpp will not need this
#include "render/window.h"
#include "system/team/team.h"
void gameplayLoop();
/*int main(){
  printf("\033[48;2;0;0;0m");
  printf("\033[2J");
  //char* title = "[PLANET] - Map Scene";
  std::string title;
  std::string planetName = "MARS";
  title = planetName + " - Map View";
  //Size size(80, 20);
  Building b(10,5,7,8);
  b.setColor(220,220,220);
  Building g(3,10,20,13);
  g.setColor(100,210,200);
  Window win(title.c_str(), 80, 20, 10, 4);
  win.addObject(b);
  //win.addObject(g);
  win.RenderScreen();
  Team t1('c');
  
  // create goofy window
  Window debug("DEBUG", 30,20,110,4);
  UI ui("goof");
  ui.addText(Text("HEY"));
  debug.RenderPanel(&ui);
  
  //while(1){
    //win.getMousePos();
  //}
  char* i = win.GetInput("Test");
  return 0;
}*/
int main(){
  gameplayLoop();
}
void gameplayLoop(){
  
}