#include "render/renderImage.h"
#include <filesystem>
#include "settings.h"
#include <iostream>
#include <cstdlib>
#include "system/utils/PerlinNoise.hpp"
#include "system/utils/rgb.h"
#include <limits>
#include "other/log.h"


//,#include "render/graphics.h"

namespace fs = std::filesystem;

Renderer* loadingRender;
Renderer* mapRender;

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

  Logger l("game");

  l.log("GameCpp", "Loading");
  JsonReader iJ(data.c_str());
  JsonReader cJ(config.c_str());

  l.log("GameCpp.load", "Reading config data");
  // read configuration data
  Json::Value configJson = cJ.read();
  // Gonna Move these to the passed in settings so that the player can decide -
  this->height = std::stoi(settings.get("height").c_str());
  this->width = std::stoi(settings.get("width").c_str());
  
  
  Json::Value infoJson   = iJ.read();
  loadingRender = new Renderer(width, height, RM_LoadScreen, &std::string("game/" + infoJson["DefaultFont"].asString()));
  std::string loadFPath = "game/" + infoJson["LoadingImages"].asString();
  //printf("\033[2J");
  //printf("\033[%d;%dH",0, 0);
  //printf("STELLAR FORTRESS IS LOADING");
 // while(1)
  
  // Load scripts
  // Load scripts
  //loadingMenu("Loading unit scripts...", "");
  
  
  l.log("GameCpp.load", "Loading teams");
  loadingMenu("Loading teams...",loadFPath);

  
  std::string teamFilePath = "game/" + infoJson["Team_Dir"].asString();
  // now we need to go through every file
  for (const auto & entry : fs::directory_iterator(teamFilePath)){
      std::string g = std::string("Loading ")+ std::string{entry.path().u8string()};
      loadingMenu(g,loadFPath);
      teams.push_back(Team(std::string{entry.path().u8string()}));
  }
  // teams have been loaded, start loading systems


  l.log("GameCpp.load", "Loading systems");
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
          //getchar();
        #endif
     // }
    } else{
      loadingMenu("Fatal ERROR, there was in fact, not a file at " + systemFilePath + "/" + systems[i].asString(),loadFPath);
    }
  }

  

  


  // End loading screen
  loadingRender->endWindow();
  delete(loadingRender); // omg im so good at memory managment 

  
  mapRender = new Renderer(width, height, RM_Game);
  mapRender->initUI(&uiMan);

  l.log("GameCpp.load", "Loading scripts");
  unitScriptMan = new ScriptManager(infoJson["Unit_Script_Dir"].asString(), ST_Unit);
  unitScriptMan->runUpdates();
  uiScriptMan = new ScriptManager(infoJson["UI_Script_Dir"].asString(), ST_UiPanel, &uiMan, mapRender);
  uiScriptMan->runUpdates();
  // throws error that dont make sense (no it dont!)
  curMap = this->systems[0].get_planet(0).get_map(); //hmm


  // we gotta switch this to a better system  
  // i kinda did ()
  while(1){
    float time = mapRender->getTime();
    //printf("Time: %d\r", (int)(time));
    if((int)(time) % 1 == 0){
      // Update screen
      uiScriptMan->runUpdates();
      mapRender->display(this->curMap.get());
    }
    if((int)time % 3 == 0){
      // Update map
      curMap = this->systems[0].get_planet(0).get_map(); //hmm
    }
    if((int)(time) % 5 == 0){
      // Update scripts
      
      unitScriptMan->runUpdates();
    }
  }
  l.log("GameCpp.load","Finished render map");
  // while(1){
  //   // Generate UI
  //   mainScreen.updateMouseInput();
  // }

  // RENDER (NOW)
  
  #ifdef VIEW_MAP
    //getchar();
  #endif
}


static void Game::loadingMenu(std::string info, std::string loadFPath){
  // add terminal image renderer? (by me)
  if(loadFPath != lastImagePath){
    //renderImage(loadFPath.c_str(),0,1);
    
    lastImagePath = loadFPath;
  }
  loadingRender->initLoadScreen(loadFPath.c_str(), info.c_str());
  loadingRender->display();
  #ifdef DEBUG
  //getchar();
  #endif
}

double scaleValue(double value, double inputMin, double inputMax, double outputMin, double outputMax) {
    double scaledValue = (value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin;
    return scaledValue;
}





void Game::InitThreads(){
  // Create threads for game

  // UI Thread
  std::thread UIThread(&Game::UIUpdate, this);
  threads.push_back(std::move(UIThread));
  // Map Thread
  std::thread MapThread(&Game::MapUpdate, this);
  threads.push_back(std::move(MapThread));
}

void Game::GameLoop(){
  
}


void Game::UIUpdate(){
  while(1){
    // Generate UI
    //mainScreen.updateMouseInput();
  }

  
}

void Game::MapUpdate(){
  
}