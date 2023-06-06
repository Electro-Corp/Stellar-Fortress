#ifndef BUTTON_H
#define BUTTON_H
class Button{
public:
  std::string text;
  void (*onClick)();
  int x,y;
  Button(std::string text, int x, int y, void (*onClick)()){
    this->text;
    this->onClick = onClick;
    this->x = x;
    this->y = y;
  }
  void click(){
    onClick();
  }
};
#endif