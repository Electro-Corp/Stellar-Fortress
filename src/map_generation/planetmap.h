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

// FOr rendering
#include "../render/graphics.h"

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

class PlanetMap {
public:
    int width;
    int height;
    std::vector<TerrainType> regions;
    PlanetMap(int sizex, int sizey, std::vector<TerrainType> r, std::vector<TerrainReq> reqs/*, int seed = 0*/);
    PlanetMap();

    std::vector<std::vector<Tile>>* get();
    void generate_map_and_colors();
    void bubble_verify();
    void bubble_verify_old();
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
  bubble_verify_old();
}

static bool verify2DTileArray(const std::vector<std::vector<Tile>>& tileArray) {
    try {
        // Iterate through rows
        for (const auto& row : tileArray) {
            // Iterate through columns
            for (const auto& tile : row) {
                // Attempt to access a member variable (e.g., x) to check if it throws an exception
                int x = tile.get_x(); // You can use any member variable that should not throw an exception
            }
        }
        return true; // No exceptions were thrown, so all elements are properly initialized
    } catch (...) {
        return false; // An exception was caught, indicating that at least one element is not properly initialized
    }
}

std::vector<std::vector<Tile>>* PlanetMap::get() {
    
    //std::vector<std::vector<Tile>> m = this->map;
    
    return &map;
}

void PlanetMap::generate_map_and_colors() {
  // Chinmay 
  // yeah
  Renderer r(800,100, RM_LoadScreen);
  // Old Code For Logger Init
  Logger l("pmap");
  l.log("PlanetMapH.generate_map_and_colors", "generating map and colors");

  // New Generation Code
  for (int y = 0; y < this->noiseMap->get_height(); y++) {
    l.log("PlanetMapH.generate_map_and_colors - Outer for-loop", "generating column " + std::to_string(y));
    std::vector<Tile> tileRow;
    
    for (int x = 0; x < this->noiseMap->get_width(); x++) {
      // Probably change this to use log instead of print (too bad now it uses a load screen)
      // we needed a "generating planet" screen anyway
      //std::cout << "PlanetMapH.generate_map_and_colors - Inner for-loop generating Tile at (" << x << ", " << y << ")" << std::endl;
      
      //l.log(s)
      // Chinmay stuff
      //r.initLoadScreen("game/basegame/images/loading/load1.bmp", std::string{"PlanetMapH.generate_map_and_colors - Inner for-loop generating Tile at (" + std::to_string(x) + ", " + std::to_string(y) + ")"}, true);
      //r.initLoadScreen("game/basegame/images/loading/load1.bmp", std::string{"Generation Progress: " + std::to_string((float)((map.size() + tileRow.size())/(this->noiseMap->get_height() + this->noiseMap->get_width())) * 100) }, true);
      //r.display(NULL, true);
      // End chinmay stuff (basiccly all the good (bad (dogshit)) stuff)
      // are you overwriting memory somewhere 
      // std::bac_alloc means that it ran out of memory
      // it allocated the max amount to the heap
      // and then on the next alloc call it realizes it cant
      // (suspicious)
      // I am not touching memory right now, maybe Wwwav 
      // :wwav so true
      // The log thing seems like it is very broken look at 
      double ch = this->noiseMap->get_map()[y][x];
      // yeah i saw that it like cuts out the generating collum sthing 
      // Temporary code to replace the region setting feature
      // TODO: make work with actual region stuff
      std::string trn = "test_region";
      
      RGB tc(ch * 100.0 ,ch * 100.0 ,ch * 100.0);
      l.log("RGB R G AND B", std::to_string(ch * 100.0));
      double cur_height = this->noiseMap->get_map()[y][x];
      for (int i = 0; i < regions.size(); ++i) {
          if (cur_height <= regions[i].height) {
              tc = regions[i].color;
              break;
          }
      }
      
      
      // creates a test tile to input into the thing
      Tile tt(tc, x, y, ch, trn);

      tileRow.push_back(tt);
    }
    r.initLoadScreen("game/basegame/images/loading/load1.bmp", std::string{"Loaded Column: " + std::to_string(y) + "\nPrevious Row had: " + std::to_string(tileRow.size())}, true);
   r.display(NULL, true);
    this->map.push_back(tileRow);
  }
  r.endWindow();
  std::cout << "Super duper cool test is about to be run this is sooooo coool";
  l.log("PlanetMapH.generate_map_and_colors", "Method finished running");
  l.log("PlanetMapH.generate_map_and_colors", "Running test method");

  // Crazy debugging
  if(!verify2DTileArray(this->map) || map.size() < 1 || map[0].size() < 1) {
    std::cout << "Super duper cool error is being thrown, good omg";
    throw TileInitializationError("Error: Planet map contains incorrectly initialized tiles.");
  }
}

/*
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
*/
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

void PlanetMap::bubble_verify_old() {
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