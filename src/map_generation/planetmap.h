#ifndef PLANETMAP_H
#define PLANETMAP_H

#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

#include "../other/log.h"
#include "../system/planet/tile.h"
#include "../render/graphics.h"
#include "../system/planet/terraintypes/terrainreqs.h"
#include "../system/utils/rgb.h"
#include "noisemap.h"
#include "biomedata.h"
#include "hhh.h"

static float average(const std::vector<float> &vals) {
  auto sum = std::reduce(
    vals.begin(),
    vals.end(),
    (float) 0,
    std::plus<float>()
  );

  return sum / vals.size();
}


class TileInitializationError : public std::exception {
public:
    TileInitializationError(const char* message) : errorMessage(message) {}

    // Override the what() function to provide an error message
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class Point {
public:  
  int x;
  int y;

  Point(int _x, int _y): x(_x), y(_y) {};
};



class PlanetMap {
public:
    int width;
    int height;

// std::vector<TerrainType> regions;
    PlanetMap(int sizex, int sizey, std::unordered_map<std::string, int> regions, std::unordered_map<int, RGB> clrs, std::unordered_map<int, HHH> hs, int _seed = 0);
    PlanetMap();

    std::vector<std::vector<Tile>>* get();

    void biome_based_generate();
    void biome_based_generate(int seed);
    

    // Old
/*
    void swag_generate_map_and_colors();
    void generate_map_and_colors_old();
    void bubble_verify();
    void bubble_verify_swag();
    void bubble_verify_old();
*/

private:
    Renderer* loadMapRender;

    std::vector<std::vector<Tile>> map;

    std::unordered_map<int, BiomeData> biomes_data;
    std::unordered_map<std::string, int> biomes_enum;
    std::unordered_map<int, RGB> colors_enum;
    std::unordered_map<int, HHH> h_enum;
    
    void gen_tile_map();
    void gen_noise();
    void gen_seeds();
    void gen_quads();
    void gen_tile_info();

    void set_biome_index();
    void set_noise_values();
    void set_colors();

    int PlanetMap::get_closest_biome_seed(int x, int y);

    NoiseMap* heightMap;
    NoiseMap* heatMap;
    NoiseMap* humidityMap;

    std::vector<Point> seed_locs;

    int seed;

    // std::vector<TerrainReq> exc;
    // std::vector<TerrainReq> req;
};



PlanetMap::PlanetMap(int sizex, int sizey, std::unordered_map<std::string, int> regions, std::unordered_map<int, RGB> clrs, std::unordered_map<int, HHH> hs, int _seed = 0) : biomes_enum(regions), colors_enum(clrs), h_enum(hs) {
    this->width = sizex;
    this->height = sizey;
    this->seed = _seed;

    biome_based_generate();
}

PlanetMap::PlanetMap(){ }

std::vector<std::vector<Tile>>* PlanetMap::get(){
  return &(map);
}

void PlanetMap::gen_tile_map()  { 
  for (int y = 0; y < this->height; y++) {
    std::vector<Tile> tileRow;
    for (int x = 0; x < this->width; x++) {
      tileRow.push_back(Tile(x,y));
    }
    this->map.push_back(tileRow);
  }
}

void PlanetMap::gen_noise() {
    this->heatMap = new NoiseMap(this->width, this->height, seed);
    this->heightMap = new NoiseMap(this->width, this->height, seed/2);
    this->humidityMap = new NoiseMap(this->width, this->height, (seed+5)/2); 
} 

void PlanetMap::set_noise_values() {
  for (int y = 0; y < this->height; y++) {
    for (int x = 0; x < this->width; x++) {
      this->map[x][y].height = heightMap->get_map()[x][y];
      this->map[x][y].heat = heatMap->get_map()[x][y];
      this->map[x][y].humidity = humidityMap->get_map()[x][y];

      auto tile_biome = this->map[x][y].b_seed;
      auto &b_data = biomes_data[tile_biome];
      b_data.add_node(this->map[x][y].height, this->map[x][y].heat, this->map[x][y].humidity);
    }
  }
}

void PlanetMap::gen_quads() {
  // Idk the scaling and stuff for this can be changed later
  int quadrant_x_divisor = (this->width >= 60 ? 12 : 6);
  int quadrant_y_divisor = (this->height >= 60 ? 12 : 6);

  int quadrant_width = this->width / quadrant_x_divisor;
  int quadrant_height = this->height / quadrant_y_divisor;

  std::default_random_engine gen_rd(seed);
  std::uniform_int_distribution<> rd_x(0, quadrant_width);
  std::uniform_int_distribution<> rd_y(0, quadrant_height);

  for (int x = 0; x < quadrant_x_divisor; x++) {
    for (int y = 0; y < quadrant_y_divisor; y++) {
      this->seed_locs.push_back(Point(rd_x(gen_rd) + x * quadrant_width, rd_y(gen_rd) + y * quadrant_height));
    }
  }
}

void PlanetMap::set_biome_index() {
  for (int row = 0; row < this->height; row++) {
    for (int col = 0; col < this->width; col++) {
      auto tile_biome = get_closest_biome_seed(col, row);

      this->map[row][col].b_seed = tile_biome;
    }
  }
}

int PlanetMap::get_closest_biome_seed(int x, int y) {
  int closest_seed_index = 0;
  int closest_seed_dist = 2147483647;

  for ( int seed_index = 0; seed_index < seed_locs.size(); seed_index++ ) {
    auto seed = seed_locs[seed_index];
    double dist = std::pow(std::pow(seed_locs[closest_seed_index].x - seed.x,2) + std::pow(seed_locs[closest_seed_index].y - seed.y,2),0.5);
    // std::cout << "dist is " << dist << " < " << closest_seed_dist << std::endl;
    if (dist < closest_seed_dist && dist != 0) {
      closest_seed_index = seed_index;
      closest_seed_dist = dist;
    }
  }
  // std::cout << "biome seed set to " << closest_seed_index << std::endl;
  return closest_seed_index;
}
// andrew fix everything it dont work it just blue (blue)
void PlanetMap::gen_tile_info() {
   Logger l("gen_tile_info");
  for(auto &x : map) {
      for(auto &y : x) { // auto = Tile
        int current_biome_index = 0;
        for(int i = 0; i < h_enum.size(); ++i) {
          if(  y.height <= h_enum.at(i).height
            && y.heat <= h_enum.at(i).heat
            && y.humidity <= h_enum.at(i).humidity
          ) {
            std::string lm = std::to_string(i) + " = biome index";
            printf("%s\n",lm.c_str());
            current_biome_index = i;
          } 
        }
        y.biome = current_biome_index;
        y.rgb = colors_enum.at(y.biome);
      }
    }
  
}


/*
 * PLANETMAP::BIOME_BASED(FUNNY)_GENERAT
 * Generates the map "based" on biomes
 authir: anduwu1 
*/
void PlanetMap::biome_based_generate() {
  // Lots of loading screens
  loadMapRender = new Renderer(500,100, RM_LoadScreen);
  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Generating Tile Map", true);
  loadMapRender->display(NULL, true);
  this->gen_tile_map();
  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Generating Noise", true);
  loadMapRender->display(NULL, true);
  this->gen_noise();
  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Generating Quads", true);
  loadMapRender->display(NULL, true);
  this->gen_quads(); 

  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Setting Noise Values", true);
  loadMapRender->display(NULL, true);
  this->set_noise_values();
  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Setting biome indices", true);
  loadMapRender->display(NULL, true);
  this->set_biome_index();

  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Computing averages", true);
  loadMapRender->display(NULL, true);
  for (auto &[_, BiomeData] : biomes_data) {
    BiomeData.compute_averages();
  }

  loadMapRender->initLoadScreen("game/basegame/images/loading/load1.bmp", "Generating tile info", true);
  loadMapRender->display(NULL, true);
  this->gen_tile_info();

  // Delete the window after we're done
  loadMapRender->endWindow();
  delete(loadMapRender);
  
  
  // In the future use wave collapse function to verify the terrain to make it better
}
#endif