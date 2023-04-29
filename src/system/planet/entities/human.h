#ifndef HUMAN_H
#define HUMAN_H
class Human{
private:
float happiness, health;
char* name;
bool isBeingAffect;
public:
  Human(char* name);

}
#include "human.cpp"
#endif