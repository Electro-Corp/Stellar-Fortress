#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include "../planet/entities/human.h"

class Team {
private: 
  std::vector<Human> Humans; 
  Json::Value TeamJson;
	std::string name, Government;
  int workCond, StartMoney, Population;
public:
	Team(std::string t);
  Team(char* t);
  std::string getTeam();
  void AddHuman(Human Person);
  inline int getWorkC() { return this->workCond; }
};
#include "team.cpp"
#endif
