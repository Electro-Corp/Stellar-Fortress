#ifndef GAME_H
#define GAME_H
#include "system/utils/readJson.h"
// teams
#include "system/team/team.h"
class Game {

  public:
    Game(std::string, std::string);
    int gameplay_loop();
  private:
    void load();
    void loadingMenu(std::string info);
  protected:
    std::string data;
    std::string config;
    int width, height;
    std::vector<Team>
};
#include "game.cpp"
#endif