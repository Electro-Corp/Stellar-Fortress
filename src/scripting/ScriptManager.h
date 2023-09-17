/*
  Manages scripts
*/
#include "../game.h"
#ifndef SCRIPTMAN_H
#define SCRIPTMAN_H
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
//
#include "script.h"
enum ScriptTypes{
  ST_Unit = 0,
  ST_UiPanel = 1,
  ST_Helper = 2
};

class ScriptManager{
private:
  std::vector<Script> scripts;

  ScriptTypes sT;
public:
  ScriptManager(std::string scriptPath, ScriptTypes sT){
    this->sT = sT;
    // Renderer r(1024, 100, RM_LoadScreen);
    for (const auto & entry : fs::directory_iterator("game/" + scriptPath)){
      std::string g = std::string("Loading ")+ std::string{entry.path().u8string()};
      std::cout << g << "\n";
      // r.initLoadScreen("", g, true);
      // r.display(NULL, true);
      std::ifstream t(std::string{entry.path().u8string()});
      std::stringstream buffer;
      buffer << t.rdbuf();
      scripts.push_back(Script(&buffer));
    }
    // r.endWindow();
  }
};
#endif