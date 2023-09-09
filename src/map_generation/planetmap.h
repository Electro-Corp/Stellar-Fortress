#ifndef PLANETMAP_H
#define PLANETMAP_H

#include <vector>
#include <random>

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
    PlanetMap(int sizex, int sizey, std::vector<TerrainType> r, std::vector<TerrainReq> reqs/*, int seed = 0*/);
    PlanetMap();

    std::vector<std::vector<Tile>> get();
    void generate_map_and_colors();
    void bubble_verify();
private:
    std::vector<std::vector<Tile>> map;
    NoiseMap* noiseMap;
    std::vector<std::vector<RGB>> colorMap;
    int seed;
    // std::vector<TerrainReq> exc;
    std::vector<TerrainReq> req;
};

PlanetMap::PlanetMap(){
  
}

PlanetMap::PlanetMap(int sizex, int sizey, std::vector<TerrainType> r, std::vector<TerrainReq> reqs/*, int seed = 0*/) {
    this->width = sizex;
    this->height = sizey;
    this->regions = r;
    this->seed = seed;
    // this->exc = excs;
    this->req = reqs;
  
    Logger l("pmap");
    l.log("PlanetMapH", "constructor");

    this->noiseMap = new NoiseMap(this->width, this->height, seed);

    l.log("PlanetMapH", "NoiseMap created succesfully");
  
    generate_map_and_colors();
    bubble_verify();
}


std::vector<std::vector<Tile>> PlanetMap::get() {
    
    std::vector<std::vector<Tile>> m = this->map;
    
    return m;
}

void PlanetMap::generate_map_and_colors() {
    Logger l("pmap");
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

/*
void PlanetMap::bubble_verify() {
  Logger l("pmap");
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, regions.size() - 1);
  bool again = true;
  
  while(again) {
    l.log("PlanetMaph.bubble_verify", "looping...");
    again = false;
    bool inc[4]{};
    
    for (int y = 0; y < this->noiseMap->get_height(); ++y) {
      for (int x = 0; x < this->noiseMap->get_width(); ++x) {
        for (int i =0; i < this->req.size(); ++i) {
          if(map[y][x].type == req[i].type) {
            int count = 0;
            try {
              if(map[y+1][x].type == req[i].comp) {
                ++count;
                inc[0] = true;
                again = true;
              }
            } catch(...) {
              l.log("PlanetMaph.bubble_verify", "TRY(0) ran into an error...");
            }
  
            try {
              if(map[y-1][x].type == req[i].comp) {
                ++count;
                inc[1] = true;
                again = true;
              }
            } catch(...) {
              l.log("PlanetMaph.bubble_verify", "TRY(1) ran into an error...");
            }
  
            try {
              if(map[y][x+1].type == req[i].comp) {
                ++count;
                inc[2] = true;
                again = true;
              }
            } catch(...) {
              l.log("PlanetMaph.bubble_verify", "TRY(2) ran into an error...");
            }
  
            try {
              if(map[y][x-1].type == req[i].comp) {
                ++count;
                inc[3] = true;
                again = true;
              }
            } catch(...) {
              l.log("PlanetMaph.bubble_verify", "TRY(4) ran into an error...");
            }
            
            l.log("PlanetMaph.bubble_verify", std::to_string(count) + " of required " + std::to_string(req[i].count) + " " + req[i].comp);
              
            if(count < req[i].count) {
              if (!inc[0]) {
                while(map[y+1][x].type == req[i].comp) {
                  int rndm = dist(gen);
                  map[y+1][x].set_r(regions[rndm]);
                  l.log("PlanetMaph.bubble_verify", "changing tile 0 to " + regions[rndm].name);
                  
                }
              }
              if (!inc[1]) {
                while(map[y-1][x].type == req[i].comp) {
                  int rndm = dist(gen);
                  map[y-1][x].set_r(regions[rndm]);
                  l.log("PlanetMaph.bubble_verify", "changing tile 1 to " + regions[rndm].name);
                }
              }
              if (!inc[2]) {
                while(map[y][x+1].type == req[i].comp) {
                  int rndm = dist(gen);
                  map[y][x+1].set_r(regions[rndm]);
                  l.log("PlanetMaph.bubble_verify", "changing tile 2 to " + regions[rndm].name);
                }
              }
              if (!inc[3]) {
                while(map[y][x-1].type == req[i].comp) {
                  int rndm = dist(gen);
                  map[y][x-1].set_r(regions[rndm]);
                  l.log("PlanetMaph.bubble_verify", "changing tile 3 to " + regions[rndm].name);
                }
              }
            }
          } 
        }
      }
    }
  }

    l.log("PlanetMaph.bubble_verify", "done looping...");
  
}
*/
/*
void PlanetMap::bubble_verify() {
  Logger l("pmap");
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, regions.size() - 1);

  bool again = true;
  while (again) {
    l.log("PlanetMap.bubble_verify", "looping...");
    again = false;
    std::vector<std::array<bool, 4>> inc(this->noiseMap->get_height(),
                                          std::array<bool, 4>{});

    for (int y = 0; y < this->noiseMap->get_height(); ++y) {
      for (int x = 0; x < this->noiseMap->get_width(); ++x) {
        for (int i = 0; i < this->req.size(); ++i) {
          if (map[y][x].type == req[i].type) {
            int count = 0;
            std::array<int, 4> dy = {1, -1, 0, 0};
            std::array<int, 4> dx = {0, 0, 1, -1};

            for (int j = 0; j < 4; ++j) {
              try {
                if (map[y + dy[j]][x + dx[j]].type == req[i].comp) {
                  ++count;
                  inc[y][j] = true;
                  again = true;
                }
              } catch (...) {
                l.log("PlanetMap.bubble_verify", "TRY(" + std::to_string(j) +
                                                      ") ran into an error...");
              }
            }

            l.log("PlanetMap.bubble_verify",
                  std::to_string(count) + " of required " +
                      std::to_string(req[i].count) + " " + req[i].comp);

            if (count < req[i].count) {
              for (int j = 0; j < 4; ++j) {
                if (!inc[y][j]) {
                  int ny = y + dy[j];
                  int nx = x + dx[j];
                  while (map[ny][nx].type == req[i].comp) {
                    int rndm = dist(gen);
                    map[ny][nx].set_r(regions[rndm]);
                    l.log("PlanetMap.bubble_verify",
                          "changing tile " + std::to_string(j) + " to " +
                              regions[rndm].name);
                    ny += dy[j];
                    nx += dx[j];
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  l.log("PlanetMap.bubble_verify", "done looping...");
}
*/

void PlanetMap::bubble_verify() {
  Logger l("pmap");
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, regions.size() - 1);

  bool again = true;
  while (again) {
    l.log("PlanetMap.bubble_verify", "looping...");
    again = false;
    std::vector<std::array<bool, 4>> inc(this->noiseMap->get_height(), std::array<bool, 4>{});

    int height = this->noiseMap->get_height();
    int width = this->noiseMap->get_width();

    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        for (int i = 0; i < this->req.size(); ++i) {
          if (map[y][x].type == req[i].type) {
            int count = 0;
            std::array<int, 4> dy = {1, -1, 0, 0};
            std::array<int, 4> dx = {0, 0, 1, -1};

            for (int j = 0; j < 4; ++j) {
              int ny = y + dy[j];
              int nx = x + dx[j];

              if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                try {
                  if (map[ny][nx].type == req[i].comp) {
                    ++count;
                    inc[y][j] = true;
                    again = true;
                  }
                } catch (...) {
                  l.log("PlanetMap.bubble_verify", "TRY(" + std::to_string(j) +
                                                    ") ran into an error...");
                }
              }
            }

            l.log("PlanetMap.bubble_verify",
                  std::to_string(count) + " of required " +
                      std::to_string(req[i].count) + " " + req[i].comp);

            if (count < req[i].count) {
              bool modified = false;
              for (int j = 0; j < 4; ++j) {
                if (!inc[y][j]) {
                  int ny = y + dy[j];
                  int nx = x + dx[j];
                  l.log("PlanetMap.bubble_verify", "while starts");
                  while (ny >= 0 && ny < height && nx >= 0 && nx < width &&
                         map[ny][nx].type == req[i].comp) {
                    int rndm = dist(gen);
                    map[ny][nx].set_r(regions[rndm]);
                    l.log("PlanetMap.bubble_verify",
                          "changing tile [" + std::to_string(ny) + "][" + std::to_string(nx) +
                              "] from " + map[ny][nx].type + " to " + regions[rndm].name);
                    inc[ny][j] = true;
                    modified = true;
                    ny += dy[j];
                    nx += dx[j];
                  }
                  l.log("PlanetMap.bubble_verify", "while ends");
                  
                }
              }
              if (modified)
                again = true;
            }
          }
        }
      }
    }
  }

  l.log("PlanetMap.bubble_verify", "done looping...");
}
#endif