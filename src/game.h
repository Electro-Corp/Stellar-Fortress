#ifndef GAME_H
#define GAME_H
#include "system/utils/readJson.h"
// teams
#include "system/team/team.h"
class Game {
  public:
    // info, config
    // inline Game(std::string d, std::string c) : data(d), config(c) {};
    Game(std::string info, std::string config);
    int gameplay_loop();
  private:
    
    void load();
    void loadingMenu(std::string info);
  protected:
    std::string data;
    std::string config;
    int width, height;
    std::vector<Team> teams; // Ha bro really forgot a semicolon
  // and a name lol bad
};
#include "game.cpp"
#endif