#ifndef GAME_H
#define GAME_H
#include "system/utils/readJson.h"
// teams
#include "system/team/team.h"
#include "system/system.h"
#include "settings.h"
#include "system/planet/tile.h"

class Game {
  public:
    // info, config
    // inline Game(std::string d, std::string c) : data(d), config(c) {};
    Game(const std::string& data, const std::string& config, Settings& settings);
    int gameplay_loop();
  private:
    
    void load();
    void loadingMenu(std::string info, std::string loadFPath);
   //  void setupSettings();
  protected:

    std::string data;
    std::string config;
    Settings settings;

    int width, height;
    std::vector<std::vector<Tile>> map;
    std::vector<Team> teams; // Ha bro really forgot a semicolon (:cri:)
    std::vector<System> systems;
  // and a name lol bad
};
#include "game.cpp"
#endif