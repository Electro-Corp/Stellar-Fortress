#include "render/renderImage.h"
std::string lastImagePath = "NO_FILE_LOADED_TET";
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
  while(1)
  loadingMenu("Loading teams...",loadFPath);
  
}
void Game::loadingMenu(std::string info, std::string loadFPath){
  
  printf("\033[%d;%dH",0, 0);
  printf("STELLAR FORTRESS IS LOADING");
  // add terminal image renderer? (by me)
  if(loadFPath != lastImagePath){
    renderImage(loadFPath.c_str(),0,1);
    lastImagePath = loadFPath;
  }
  printf("\033[%d;%dH",height, 0);
  printf("%s\n",info.c_str());
}

int Game::gameplay_loop() {
  return 0;
}

