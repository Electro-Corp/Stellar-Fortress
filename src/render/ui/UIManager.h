/*
  Class that handles and manages UI Panels
  Optimally all the UI Panels would be loaded from scripts
*/
#ifndef UI_MAN
#define UI_MAN
#include "ui.h"
class UIManager{
private:
std::vector<UI> uis;
public:
  UIManager(){
    
  }

  void addUIPanel(UI ui){
    this->uis.push_back(ui);
  }

  std::vector<UI> getUIs(){
    return uis;
  }
};
#endif