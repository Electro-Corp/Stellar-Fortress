#include <vector>
#include "text.h"
class UI{
public: // Whats this for windows that display information cool I read me d it up
  std::vector<Text> texts;
  char* title;
// By that I mean I wrote stuff
  UI(char* title){
    this->title = title;
  }
  void addText(Text t){
    this->texts.push_back(t);
  }

  
};