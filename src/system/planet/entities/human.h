#ifndef HUMAN_H
#define HUMAN_H
#include "../../team/team.h"
class Human{
private:
  int x, y;
  float happiness, health;
  char* name;
  Team* loyalTeam;
  bool isBeingAffect;
public:
  Human(char* name);
  Human(char*, int, int, Team*);
  void Move(int direction);
  char* Statement();
};
#include "human.cpp"
#endif