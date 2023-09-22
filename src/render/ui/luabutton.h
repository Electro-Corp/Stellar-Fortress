/*
  Class for buttons to be accessed by Lua
*/
#ifndef LUABUTTON_H
#define LUABUTTON_H
#include <string>
class Lua_Button{
public:
  Lua_Button();
  Lua_Button(std::string text, int x, int y, std::string luaOnClick){
    this->text = text;
    this->x = x;
    this->y = y;
    this->luaOnClick = luaOnClick;
  }

  std::string getText() const {return text;}
  std::string getluaOnClick() const {return luaOnClick;}
  int getX() const {return x;}
  int getY() const {return y;}
  void setText(std::string text){this->text = text;}
  void setluaOnClick(std::string luaOnClick){this->text = luaOnClick;}
  void setX(int x){this->x = x;}
  void setY(int y){this->y = y;}
private:
int x, y;
std::string text, luaOnClick;
};
#endif