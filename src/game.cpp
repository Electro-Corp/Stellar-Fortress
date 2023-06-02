#include "render/renderImage.h"
#include <filesystem>
#include "settings.h"
#include <iostream>
#include <cstdlib>
#include "system/utils/PerlinNoise.hpp"
#include "system/utils/rgb.h"
#include <limits>
#include "other/log.h"

namespace fs = std::filesystem;


// #define DEBUG 1
#define VIEW_MAP 1

double scaleValue(double value, double inputMin, double inputMax, double outputMin, double outputMax);

static double inverseLerp(double xx, double yy, double value);
std::string lastImagePath = "NO_FILE_LOADED_YET";

Game::Game(const std::string& data, const std::string& config, Settings& settings){
  this->data = data;
  this->config = config;
  this->settings = settings;
  // LoggerInit();
  load(); 
}

// Look at the loading section in the design notes
void Game::load(){
  JsonReader iJ(data.c_str());
  JsonReader cJ(config.c_str());
  // read configuration data
  Json::Value configJson = cJ.read();
  // Gonna Move these to the passed in settings so that the player can decide -
  this->height = std::stoi(settings.get("height").c_str());
  this->width = std::stoi(settings.get("width").c_str());

  
  Json::Value infoJson   = iJ.read();
  std::string loadFPath = "game/" + infoJson["LoadingImages"].asString();
  printf("\033[2J");
  printf("\033[%d;%dH",0, 0);
  printf("STELLAR FORTRESS IS LOADING");
 // while(1)
  loadingMenu("Loading teams...",loadFPath);

  
  std::string teamFilePath = "game/" + infoJson["Team_Dir"].asString();
  // now we need to go through every file
  for (const auto & entry : fs::directory_iterator(teamFilePath)){
      std::string g = std::string("Loading ")+ std::string{entry.path().u8string()};
      loadingMenu(g,loadFPath);
      teams.push_back(Team(std::string{entry.path().u8string()}));
  }
  // teams have been loaded, start loading systems


  loadingMenu("Loading systems...", loadFPath);
  std::string systemFilePath = "game/" + infoJson["Systems_Dir"].asString();
  Json::Value systems = infoJson["Systems"];

  for (int i = 0; i < systems.size(); i++) {   
    if(!fs::is_directory(systemFilePath + "/"+ systems[i].asString())) {
      // for(int j=0; j<10; j++) { 
        std::string g = systemFilePath + "/" + systems[i].asString();
        loadingMenu(g,loadFPath);
        this->systems.push_back(System(g));
      
        #ifdef DEBUG
          getchar();
        #endif
     // }
    } else{
      loadingMenu("Fatal ERROR, there was in fact, not a file at " + systemFilePath + "/" + systems[i].asString(),loadFPath);
    }
  }

  
  // Perlin Noise Generation Settings and stuff
  // std::string name = "test";
  // float s = 1;
  // int f = 10;

  Logger l("test1");
  l.log("GameCpp.load", "Generating test planet");
  Planet tPlanet("name", 30);
  l.log("GameCpp.load", "Done generating test planet");
  
  curMap = tPlanet.get_map();
  
  Window win(settings.get("Name").c_str(), configJson["width"].asInt(), configJson["height"].asInt(), 0, 0);
  system("clear");
  // I will fix just need to change the other things
  // All you would have to do is add like a ->get()
  win.RenderMap(this->curMap->get());

  

  #ifdef VIEW_MAP
    getchar();
  #endif
}


void Game::loadingMenu(std::string info, std::string loadFPath){
  // add terminal image renderer? (by me)
  if(loadFPath != lastImagePath){
    renderImage(loadFPath.c_str(),0,1);
    lastImagePath = loadFPath;
  }
  printf("\033[%d;%dH",height, 0);
  printf("%s\n",info.c_str());
  #ifdef DEBUG
  getchar();
  #endif
}

std::vector<std::vector<RGB>> Game::generate_colors() {
  std::vector<std::vector<RGB>> colorMap;
  for(int y = 0; y < this->height; ++y) {
    std::vector<RGB> l; colorMap.push_back(l);
    for(int x = 0; x < this->width; ++x) {
      double cur_height = this->noiseM[y][x];
      for(int i=0;i < regions.size(); ++i) {
        if(cur_height <= regions[i].height) { // Im doing something right if it goes wrong
          colorMap[y].push_back(regions[i].color); // why it blue (is it supposed to be (blu))
          break;
        }
      }
    }
  }
  return colorMap;
}


double scaleValue(double value, double inputMin, double inputMax, double outputMin, double outputMax) {
    double scaledValue = (value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin;
    return scaledValue;
}