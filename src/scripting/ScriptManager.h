/*
  Manages scripts
*/
#include "../game.h"
#ifndef SCRIPTMAN_H
#define SCRIPTMAN_H
#include <vector>
#include <filesystem>
#include <memory>
#include <fstream>
namespace fs = std::filesystem;

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

// Include UI
#include "../render/ui/UIManager.h"
#include "../render/ui/ui.h"


enum ScriptTypes{
  ST_Unit = 0,
  ST_UiPanel = 1,
  ST_Helper = 2
};


class ScriptManager{
private:
  lua_State* luaState;
// Vectors to hold all the functions
  std::vector<luabridge::LuaRef> updates;
  std::vector<luabridge::LuaRef> inits;
  UIManager uiMan;
  ScriptTypes sT;
public:
  ScriptManager(std::string scriptPath, ScriptTypes sT){
    this->sT = sT;
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
    for (const auto & entry : fs::directory_iterator("game/" + scriptPath)){
        std::ifstream file(entry.path().u8string());
        int scriptLoadStatus = luaL_dofile(luaState, entry.path().u8string().c_str());
        updates.push_back(luabridge::getGlobal(luaState, "update"));
        if(sT == ST_UiPanel){
          // Read init function
          inits.push_back(luabridge::getGlobal(luaState, "init"));
        }
       
    }
    if(sT == ST_UiPanel){
      runInits();
    }
  } 
  void runUpdates(){
    for(luabridge::LuaRef &ref : updates){
      // Execute the update function
      ref(); // pass in args based on the script type (later)
    }
  }
  void runInits(){
    if(sT == ST_UiPanel){
      luabridge::getGlobalNamespace(luaState)
        .beginClass<UI>("UI")
        .addConstructor<void(*) (char*, int)>()
        .addProperty("title", &UI::getTitle, &UI::setTitle)
        .addProperty("index", &UI::getIndex, &UI::setIndex)
        //.addFunction("addText", &UI::addText)
        .endClass();
        int c = 0;
        for(luabridge::LuaRef &ref : inits){
          // Execute the init function
          UI tmp("NULL", c++);
          UI res1 = ref(tmp);
          //tmp = res1;
          //printf("Panel title: %s\n",res1.getTitle());
          std::cout << "Panel Title: "<<res1.getTitle()<< "\n";
          uiMan.addUIPanel(res1);
        }
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