#ifndef UI_H
#define UI_H
#include <vector>
#include <string>
#include "text.h"
#include "button.h"
class UI{
public: // Whats this for windows that display information cool I read me d it up
  
// By that I mean I wrote stuff
  UI(std::string m_title, int m_index) : title(m_title), index(m_index){
  }
  UI(){
    
  }
  void addText(Text t)  {
    this->texts.push_back(t);
  }
  void setTitle(std::string title) {
    this->title = title;
  }
  std::string getTitle() const {
    return title;
  }
  void setIndex(int index){this->index = index;}
  int getIndex() const {return index;}
private:
  std::vector<Text> texts;
  //std::vector<Button> buttons;
  int index;
  std::string title;
};
#endif