#include "render/renderImage.h"
#include <filesystem>
namespace fs = std::filesystem;
#define DEBUG 1
std::string lastImagePath = "NO_FILE_LOADED_YET";
Game::Game(std::string data, std::string config){
  this->data = data;
  this->config = config;
  printf("DEBUG_GAME_STARTED\n");
  load();
}
void Game::load(){
  JsonReader iJ(data.c_str());
  JsonReader cJ(config.c_str());
  // read configuration data
  Json::Value configJson = cJ.read();
  this->width = configJson["GameWidth"].asInt();
  this->height = configJson["GameHeight"].asInt();
  Json::Value infoJson   = iJ.read();
  std::string loadFPath = "game/" + infoJson["LoadingImages"].asString();
  printf("\033[2J");
  printf("\033[%d;%dH",0, 0);
  printf("STELLAR FORTRESS IS LOADING");
 // while(1)
  loadingMenu("Loading teams...",loadFPath);
  // Load teams from team json
  std::string teamFilePath = "game/" + infoJson["Team_Dir"].asString();
  // now we need to go through every file
  for (const auto & entry : fs::directory_iterator(teamFilePath)){
      std::string g = std::string("Loading ")+ std::string{entry.path().u8string()};
      loadingMenu(g,loadFPath);
      teams.push_back(Team(std::string{entry.path().u8string()}));
  }
  // teams have been loaded, start loading systems
  loadingMenu("Loading systems...",loadFPath);
  std::string systemFilePath = "game/" + infoJson["Systems_Dir"].asString();
  for (const auto & entry : fs::directory_iterator(teamFilePath)){
      if(fs::is_directory(entry)){
        // Load the system inside
        for (const auto & systemJson : fs::directory_iterator(std::string{entry.path().u8string()})){
          if(!fs::is_directory(entry)){
            systems.push_back(System(std::string{entry.path().u8string()}));
          }
        }
      }else{
        printf("\033[2J");
        printf("\033[%d;%dH",0, 0);
        printf("Fatal Error:\n");
        printf("Detected non-directory in root system directory (%s), quitting.\n",systemFilePath.c_str());
      }
  }
  

  //JsonReader tJ(teamFilePath.c_str());

  
}



void Game::setupSettings() {
  
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

int Game::gameplay_loop() {
  return 0;
}

