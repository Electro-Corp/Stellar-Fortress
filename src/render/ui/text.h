class Text{
public:
  std::string text;
  int x,y;
  Text(std::string text, bool bold, int x, int y){
    this->text = text;
    if(bold){
      text = text + "\e[1m";
    }
    this->x = x;
    this->y = y;
  }
};