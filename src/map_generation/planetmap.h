#ifndef PLANETMAP_H
#define PLANETMAP_H

#include <vector>
#include "../other/log.h"
#include "../system/planet/tile.h"
#include "../system/planet/terraintypes/terrainreqs.h"
#include "../system/utils/rgb.h"
#include "./noisemap.h"
#include "colormap.h"

class PlanetMap {
public:
    int width;
    int height;
    std::vector<TerrainType> regions;
    PlanetMap(int size, std::vector<TerrainType> r, int seed = 0);
    std::vector<std::vector<Tile>> get();
    void generate_map_and_colors();
    void bubble_verrify();
private:
    std::vector<std::vector<Tile>> map;
    NoiseMap* noiseMap;
    std::vector<std::vector<RGB>> colorMap;
    int seed;
    std::vector<TerrainReq> exc;
    std::vector<TerrainReq> req;
};

PlanetMap::PlanetMap(int size, std::vector<TerrainType> r, std::vector<TerrainReq> excs, std::vector<TerrainReq> reqs, int seed = 0) {
    this->width = size;
    this->height = size;
    this->regions = r;
    this->seed = seed;
    this->exc = excs;
    this->req = reqs;
  
    Logger l("test1");
    l.log("PlanetMapH", "Const");

    this->noiseMap = new NoiseMap(this->width, this->height, seed);

    l.log("PlanetMapH", "NoiseMap created succesfully");
  
    generate_map_and_colors();
    
}


std::vector<std::vector<Tile>> PlanetMap::get() {
    return this->map;
}

void PlanetMap::generate_map_and_colors() {
    Logger l("test1");
    l.log("PlanetMapH.generate_map_and_colors", "generating map and colors");

    for (int y = 0; y < this->noiseMap->get_height(); ++y) {
        std::vector<Tile> tileRow;
        std::vector<RGB> colorRow;
        for (int x = 0; x < this->noiseMap->get_width(); ++x) {
            double cur_height = this->noiseMap->get_map()[y][x];
            RGB color;
            std::string t;
            for (int i = 0; i < regions.size(); ++i) {
                if (cur_height <= regions[i].height) {
                    color = regions[i].color;
                    t = regions[i].name;
                    break;
                }
            }
            Tile tile(color, x, y, cur_height, t);
            tileRow.push_back(tile);
            colorRow.push_back(color);
        }
        this->map.push_back(tileRow);
        this->colorMap.push_back(colorRow);
    }
    l.log("PlanetMapH.generate_map_and_colors", "done generating map and colors");
}

void PlanetMap::bubble_verrify() {
  for (int y = 0; y < this->noiseMap->get_height(); ++y) {
    for (int x = 0; x < this->noiseMap->get_width(); ++x) {
      for (int i =0; i < this-> req.size(); ++i) {
        if(map[y][x].type == req[i].type) {
          int count = 0;
          
          try {
            if(map[y+1][x].type == req[i].comp) {
              ++count;
            }
          } catch(...) { }

          try {
            if(map[y-1][x].type == req[i].comp) {
              ++count;
          } catch(...) { }

          try {
            if(map[y][x+1].type == req[i].comp) {
              ++count;
          } catch(...) { }

          try {
            if(map[y][x-1].type == req[i].comp) {
              ++count;
          } catch(...) { }

          Logger l("bubbly ver");
          l.log("bub", std::to_string(count));
          break;
        }
      }
    }
  }
}
#endif
