// Lookup table
char*[] adj = {"great","amazing","good","ok","fine","bad","terrible"}; // Adj


Human::Human(char* name, int x, int y){
  this->name = name;
  this->x = x;
  this->y = y;
}
char* Human::Statment(){
  
} 
// The directions start at North and go clock wise increasing. I.E 1 for north 2 for north east etc.
void Human::Move(int direction){
  switch (direction) {
  case 1:
    y--; 
    break;
  case 2:
    y--;
    x++;
    break;
  case 3:
    x++;
    break;
  case 4:
    x++;
    y++;
    break;
  case 5:
    y++;
    break;
  case 6:
    y++;
    x--;
    break;
  case 7:
    x--;
    break;
  case 8:
    x--;
    y--;
    break;
}

}
