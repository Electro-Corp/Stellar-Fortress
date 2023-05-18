#include "render/renderImage.h"
#include "render/window.h"
#include <filesystem>
#include "settings.h"
#include<iostream>
#include<cstdlib>
#include "system/utils/PerlinNoise.hpp"
#include "system/utils/rgb.h"

namespace fs = std::filesystem;
// #define DEBUG 1


std::string lastImagePath = "NO_FILE_LOADED_YET";

Game::Game(const std::string& data, const std::string& config, Settings& settings){
  this->data = data;
  this->config = config;
  this->settings = settings;
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
  this->width = std::stoi(settings.get("width").c_str()); // 
  
  // loadingMenu(settings.get("height"), "NO_FILE_LOADED_YET");
  // #ifdef DEBUG
  // getchar();
  // #endif
  // hy idk why no work
  // the old version worked
  // ya and this is better is it tho
  // I do better
  // --------------------------------------------------------------------------
  
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
      loadingMenu("Fatal ERROR, there was in fact, not a file at " + systemFilePath +"/"+ systems[i].asString(),loadFPath);
    }
  }

  // Perlin Noise Generation Settings and stuff
  const double frequency = 8; // Idk this value can be messed with. Range - [0.1 .. 64.0]
  const std::int32_t octaves = 6; // Same. Range - [1 .. 16]
  siv::PerlinNoise::seed_type seed; // Range - [0 .. 2^32-1]
  if(this->settings.get("seed").compare("") != 0) {
     seed = std::stoi(settings.get("seed"));
  } else {
    srand((unsigned) time(NULL));
    seed = rand();
  }
  
  const siv::PerlinNoise perlin{ seed };
  
  const double fx = (frequency / this->width);
	const double fy = (frequency / this->height);

  for (std::int32_t y = 0; y < this->height; ++y) {
      std::vector<Tile> l;
      this->map.push_back(l);
			for (std::int32_t x = 0; x < this->width; ++x) {
				RGB color(perlin.octave2D_01((x * fx), (y * fy), octaves));
	      Tile t(color, x, y, false);
        this->map[y].push_back(t);
			}
		}

  #ifdef DEBUG
  getchar();
  #endif

  Window win(settings.get("Name").c_str(), configJson["width"].asInt(), configJson["height"].asInt(), 0, 0);
  system("clear");
  win.RenderMap(this->map);
  while(1){}
  
}




void Game::loadingMenu(std::string info, std::string loadFPath){
  // add terminal image renderer? (by me)
  if(loadFPath != lastImagePath){
    renderImage(loadFPath.c_str(),0,1);
    lastImagePath = loadFPath;
  } //else { // You dont have enough images for this to make sense
    // renderImage(loadFPath.c_str(),0,1);
  // }
  printf("\033[%d;%dH",height, 0);
  printf("%s\n",info.c_str());
  #ifdef DEBUG
  getchar();
  #endif
}

int Game::gameplay_loop() {
  return 0;
}

