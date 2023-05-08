
// Lookup table
// char* adj[] = {"great","amazing","good","ok","fine","bad","terrible"}; // Adj

#include "human.h"
/*
Human::Human(char* name, int x, int y, Team* whichTeam) : GameObject() {
  this->name = name;
  this->loyalTeam = whichTeam;
  // Need to define locaiton
  // Happiness starts at 50 if everything is at a normal level. todo: add living conditions to this
  this->happiness = (50 + ((this->loyalTeam->getWorkC()-5) * 2));
}
*/

Human::Human(char* name, int x, int y, Team* whichTeam) : GameObject(x, y) {
  this->name = name;
  // this->x = x;
  // this->y = y;
  this->loyalTeam = whichTeam;
  //Happiness starts at 50 if everything is at a normal level. todo: add living conditions to this
  this->happiness = (50 + ((this->loyalTeam->getWorkC()-5) * 2));
}

/*char* Human::Statement(){
  
} */
// The directions start at North and go clock wise increasing. I.E 1 for north 2 for north east etc. 
/*
void Human::Move(int direction){
  switch (direction) {
    case 1:
      this->y--; 
      break;
    case 2:
      this->y--;
      this->x++;
      break;
    case 3:
      this->x++;
      break;
    case 4:
      this->x++;
      this->y++;
      break;
    case 5:
      this->y++;
      break;
    case 6:
      this->y++;
      this->x--;
      break;
    case 7:
      this->x--;
      break;
    case 8:
      this->x--;
      this->y--;
      break;
  }

}
*/