#ifndef UI_H
#define UI_H
#include <vector>
#include <string>
#include "text.h"
#include "button.h"
#include "luabutton.h"
class UI{
public: 
  UI(std::string m_title, int m_index, int m_width, int m_height) : title(m_title), index(m_index) , width(m_width), height(m_height){
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
  std::string getTitle() const {
    return title;
  }
  int getHeight() const {return height;}
  int getWidth() const{return width;}
  void setIndex(int index){this->index = index;}
  int getIndex() const {return index;}
private:
  std::vector<Text> texts;
  std::vector<Lua_Button> buttons;
  int index, width, height;
  std::string title;
};
#endif