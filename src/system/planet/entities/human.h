#ifndef HUMAN_H
#define HUMAN_H

#include "../../team/team.h"
#include "../gameObject.h"

class Human : public GameObject {
  private:
    float happiness, health;
    char* name;
    Team* loyalTeam;
    bool isBeingAffect;
  public:
    //Human(char* name);
    Human(char*, int, int, Team*) /* : GameObject(int, int)*/;
    // void Move(int);
    //char* Statement();
};
#include "human.cpp"
#endif