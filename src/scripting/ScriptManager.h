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
#include "../../gm/gmMachine.h"
#include "../../gm/gmCall.h" // Header contains helper class

extern gmMachine machine; // Virtual Machine instance
enum ScriptTypes{
  ST_Unit = 0,
  ST_UiPanel = 1,
  ST_Helper = 2
};


class ScriptManager{
private:
  std::vector<gmCall> scripts;
  ScriptTypes sT;
public:
  ScriptManager(std::string scriptPath, ScriptTypes sT){
    this->sT = sT;
    for (const auto & entry : fs::directory_iterator("game/" + scriptPath)){
        std::ifstream file(entry.path().u8string());
        std::string fileString = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        machine.ExecuteString(fileString.c_str());
        file.close();
        // Load update function
        gmCall call;
        call.BeginGlobalFunction(&machine, "update");
    }
  } 
  void runUpdates(){
    for(gmCall &call : scripts){
      call.End();
    }
  }
};
/*class ScriptManager{
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

  void runUpdateFuncs(){
    for(Script &script : scripts){
      
    }
  }
};*/
#endif