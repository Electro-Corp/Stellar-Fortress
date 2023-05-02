#ifndef HUMAN_H
#define HUMAN_H
class Human{
private:
int x, y;
float happiness, health;
char* name;
bool isBeingAffect;
public:
  Human(char* name);
  Move(int direction);
}
#include "human.cpp"
#endif