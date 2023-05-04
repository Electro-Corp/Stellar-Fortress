#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include "../planet/entities/human.h"
class Human;
class Team {
private: 
  std::vector<Human> Humans; 
  Json::Value TeamJson;
	std::string name, Government;
  int WorkCond, StartMoney, Population;
public:
	Team(std::string name);
  Team(char* name);
  char* getName();
  int getWorkC();
};
#endif
