#ifndef TEAM_H
#define TEAM_H
#include <vector>
class Team {
private:
	char* name;
  int workCond, Democracy, StartMoney, Population;
public:
	Team(char*);
  char* getName();
};
#endif
