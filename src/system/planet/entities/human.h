#ifndef HUMAN_H
#define HUMAN_H

#include "../gameObject.h"

class Team;

class Human : public GameObject {
  private:
    float happiness, health;
    char* name;
    Team& loyalTeam;
    bool isBeingAffect;
  public:
    //Human(char* name);
    Human(char*, int, int, Team&) /* : GameObject(int, int)*/;
    // void Move(int);
    //char* Statement();
};

#endif