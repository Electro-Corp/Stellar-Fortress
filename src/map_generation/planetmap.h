#ifndef PLANETMAP_H
#define PLANETMAP_H

#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <map>

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

    void add_biome_nodes();

    int PlanetMap::get_closest_biome_seed(int x, int y);

    NoiseMap* heightMap;
    NoiseMap* heatMap;
    NoiseMap* humidityMap;

    std::vector<Point> seed_locs;

    int seed;
  
    // Renderer 
    Renderer *r;

    // std::vector<TerrainReq> exc;
    // std::vector<TerrainReq> req;
};



PlanetMap::PlanetMap(int sizex, int sizey, std::unordered_map<std::string, int> regions, std::unordered_map<int, RGB> clrs, std::unordered_map<int, HHH> hs, int _seed = 0) : biomes_enum(regions), colors_enum(clrs), h_enum(hs) {
    this->width = sizex;
    this->height = sizey;
  if (seed == 0) {
    std::random_device rd;
    std::map<int, int> hist;
    std::uniform_int_distribution<int> dist(1000, 514227);
    this->seed = dist(rd);
  } else {
    this->seed = _seed;
  }
  // Init the renderer
  r = new Renderer(500, 200, RM_LoadScreen);
   
  biome_based_generate();
}

PlanetMap::PlanetMap(){ }

std::vector<std::vector<Tile>>* PlanetMap::get(){
  return &(map);
}

void PlanetMap::gen_tile_map()  { 
  r->initLoadScreen("bruh", "Generating Tile Map", true);
  for (int y = 0; y < this->height; y++) {
    std::vector<Tile> tileRow;
    for (int x = 0; x < this->width; x++) {
      tileRow.push_back(Tile(x,y));
    }
    r->initLoadScreen("bruh", std::string{"Generating Tile Map Row: " + std::to_string(y)}, true);
    r->display();
    this->map.push_back(tileRow);
  }
}

void PlanetMap::gen_noise() {
    r->initLoadScreen("null", "Generating Heat Map", true);
    r->display();
    this->heatMap = new NoiseMap(this->width, this->height, seed);
    r->initLoadScreen("null", "Generating Height Map", true);
    r->display();
    this->heightMap = new NoiseMap(this->width, this->height, seed/2);
    r->initLoadScreen("null", "Generating Humidity Map", true);
    r->display();
    this->humidityMap = new NoiseMap(this->width, this->height, (seed+5)/2); 
} 

void PlanetMap::set_noise_values() {
  
  // //Logger l("Set_Noise_Values");
  for (int y = 0; y < this->height; y++) {
    r->initLoadScreen("trash", std::string{"Set noise at : " + std::to_string(y)}, true);
    r->display();
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
  r->initLoadScreen("trash","Generating Quads", true);
  r->display();
  // Idk the scaling and stuff for this can be changed later
  int quadrant_x_divisor = (this->width >= 60 ? 12 : 6);
  int quadrant_y_divisor = (this->height >= 60 ? 12 : 6);

  int quadrant_width = this->width / quadrant_x_divisor;
  int quadrant_height = this->height / quadrant_y_divisor;

  std::default_random_engine gen_rd(seed);
  std::uniform_int_distribution<> rd_x(0, quadrant_width);
  std::uniform_int_distribution<> rd_y(0, quadrant_height);

  for (int x = 0; x < quadrant_x_divisor; x++) {
    r->initLoadScreen("trash", std::string{"Gen quad X: " + std::to_string(x)}, true);
    r->display();
    for (int y = 0; y < quadrant_y_divisor; y++) {
      this->seed_locs.push_back(Point(rd_x(gen_rd) + x * quadrant_width, rd_y(gen_rd) + y * quadrant_height));
    }
  }
}

void PlanetMap::set_biome_index() {
  // //Logger l("set_biome_index");
  for (int row = 0; row < this->height; row++) {
    r->initLoadScreen("trash", std::string{"Set biome index: " + std::to_string(row)}, true);
    r->display();
    for (int col = 0; col < this->width; col++) {
      int tile_biome = get_closest_biome_seed(row, col);
      // std::stringstream lm;
      
      // lm << "(" << row << ", " << col << ") - Biome: " << tile_biome << std::endl;
      // ////l.log(lm.str());
      this->map[row][col].b_seed = tile_biome;
    }
  }
}

int PlanetMap::get_closest_biome_seed(int x, int y) {
  int closest_seed_index = 0;
  int closest_seed_dist = 2147483647;
  // //Logger l("dist");

  for ( int seed_index = 0; seed_index < seed_locs.size(); seed_index++ ) {
    auto seed = seed_locs[seed_index];
    double dist = std::pow(std::pow((double) (seed.x - x),2) + std::pow((double) seed.y - y,2),0.5);
    
    if (dist < closest_seed_dist && dist > 2) {
      closest_seed_index = seed_index;
      closest_seed_dist = dist;
    }
  }

  // ////l.log(std::to_string(closest_seed_dist));
  return closest_seed_index;
}


void PlanetMap::gen_tile_info() {
  for (auto &[_, biome_data] : biomes_data) {
    int bi = 0;
    for (int i = 0; i < h_enum.size(); i++) {
      if(biome_data.average_height() >= h_enum.at(i).height && biome_data.average_heat() >= h_enum.at(i).heat && biome_data.average_humidity() >= h_enum.at(i).humidity) {
        bi = i;
      }
    }
    biome_data.biome_index = bi;
  }

  for(auto &row : map) {
    for(auto &tile : row) {
      tile.biome = biomes_data[tile.b_seed].biome_index; // this does it? // this sets biome and color
      tile.rgb = colors_enum[tile.biome];
    }
  }
}

// TODO: Something here is causing segfault (not anymore)
// Move this into generate noise to speed it up by having less for loops
void PlanetMap::add_biome_nodes() {
  for(auto &row : map) {
    for(auto &tile : row) {
      biomes_data[tile.b_seed].add_node(tile.height, tile.heat, tile.humidity);
    }
  }
}

/*
 * PLANETMAP::BIOME_BASED(FUNNY)_GENERAT
 * Generates the map "based" on biomes
 authir: anduwu1 
*/
void PlanetMap::biome_based_generate() {
  // Lots of loading screens // No more
  this->gen_tile_map();
  this->gen_noise();
  this->gen_quads(); 

  this->set_noise_values();
  this->set_biome_index();

  r->initLoadScreen("trash", "Adding biome nodes...", true);
  r->display();
  this->add_biome_nodes();

  for (auto &[_, biome_data] : biomes_data) {
    biome_data.compute_averages();
  }
  
  r->initLoadScreen("trash", std::string{"Gen Tile Info"}, true);
  r->display();
  this->gen_tile_info();

  /* for (auto &[_, biome_data] : biomes_data) {
    std::cout << biome_data.average_height() << std::endl;
  } */
  // In the future use wave collapse function to verify the terrain to make it better
}
#endif