#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../../scripting/script.h"
class  GameObject {
protected:
  int x, y;
  Script *script;
private:

public:
  GameObject(int, int, Script*);
  void update();
  void userMove();
  void uiShow();
};
#include "gameObject.cpp"
#endif