#include "render/renderImage.h"
#include <filesystem>
#include "settings.h"
namespace fs = std::filesystem;
// #define DEBUG 1


std::string lastImagePath = "NO_FILE_LOADED_YET";


Game::Game(const std::string& data, const std::string& config, Settings& settings ){
  this->data = data;
  this->config = config;
  this->settings = settings;
  load(); 
}

// Look at the loading section in the design notes
void Game::load(){

  // setupSettings();

  
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
      loadingMenu("Fatal ERROR, there was in fact, not a file at "+ systemFilePath +"/"+ systems[i].asString(),loadFPath);
    }
  }

  #ifdef DEBUG
  getchar();
  #endif

  // while(1) {
    
  // }
  
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

