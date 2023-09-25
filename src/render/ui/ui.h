#ifndef UI_H
#define UI_H
#include <vector>
#include <string>
#include "text.h"
#include "button.h"
#include "luabutton.h"
class UI{
public: 
  UI(std::string m_title, int m_index, int m_width, int m_height, int m_x, int m_y) : title(m_title), index(m_index) , width(m_width), height(m_height), x(m_x), y(m_y){
  }
  UI(){
    
  }
  void addText(Text t)  {
    this->texts.push_back(t);
  }
  void addButton(Lua_Button b){
    this->buttons.push_back(b);
  }
  void setTitle(std::string title) {
    this->title = title;
  }
  void setWidth(int width){this->width = width;}
  void setHeight(int height){this->height = height;}
  void setX(int x){this->x = x;}
  void setY(int y){this->y = y;}
  std::string getTitle() const {
    return title;
  }
  int getHeight() const {return height;}
  int getWidth() const{return width;}
  int getX() const {return x;}
  int getY() const{return y;}
  void setIndex(int index){this->index = index;}
  int getIndex() const {return index;}

  std::vector<Text> getTexts() const { return texts;}
private:
  std::vector<Text> texts;
  std::vector<Lua_Button> buttons;
  int index, width, height, x, y;
  std::string title;
};
#endif