#ifndef TEXT_H
#define TEXT_H
class Text{
public:
  Text(){}

  Text(std::string text, int x, int y){
    this->text = text;
    this->x = x;
    this->y = y;
  }

  std::string getText() const {return text;}
  int getX() const {return x;}
  int getY() const {return y;}
  void setText(std::string text){this->text = text;}
  void setX(int x){this->x = x;}
  void setY(int y){this->y = y;}
private:
  std::string text;
  int x,y;
};
#endif