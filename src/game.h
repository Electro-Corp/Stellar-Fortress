#ifndef GAME_H
#define GAME_H
#include "system/utils/readJson.h"
// teams
#include "system/team/team.h"
#include "system/system.h"
#include "settings.h"
#include "system/planet/tile.h"
#include "render/window.h"
#include "system/planet/terraintypes/terraintype.h"
#include "./map_generation/planetmap.h"

class Game {
  public:
    Game(const std::string& data, const std::string& config, Settings& settings);
    int gameplay_loop();
    RGB make_color_grey(const RGB& rgb, double scale_factor);

    std::vector<TerrainType> regions;
    std::vector<std::vector<RGB>> colorM;
  private:
    
    void load();
    void loadingMenu(std::string info, std::string loadFPath);
    // std::vector<std::vector<double>> generateNoise();
    std::vector<std::vector<double>> noiseM;    
    void init_map();
    std::vector<std::vector<RGB>> generate_colors();
    void generate_terrain_types();
    std::vector<std::vector<Tile>> generate_map();
    int render_from_pmap(PlanetMap pm);
  protected:
    PlanetMap* curMap;
    std::string data;
    std::string config;
    Settings settings;

    int width, height;
    std::vector<std::vector<Tile>> map;
    std::vector<Team> teams; // Ha bro really forgot a semicolon (:cri:)
    std::vector<System> systems;
    

    //(char* title, int width, int height, int x, int y)
    // char* t_name = "Tech-Tree";
    // Window Tech(t_name,20,50,30,30);
    
  // and a name lol bad
};
#include "game.cpp"
#endif