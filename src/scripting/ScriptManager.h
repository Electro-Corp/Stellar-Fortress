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
// Include graphics
#include "../render/graphics.h"


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
  ScriptTypes sT;
  UIManager* uiMan;
  std::unique_ptr<UIManager> uiManGlob;
  std::unique_ptr<Renderer> renderManGlob;
public:
  ScriptManager(std::string scriptPath, ScriptTypes sT, UIManager* uiMan = nullptr, Renderer* renderMan = nullptr) {
    this->sT = sT;
    
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
    for (const auto & entry : fs::directory_iterator("game/" + scriptPath)){
        std::ifstream file(entry.path().u8string());
        int scriptLoadStatus = luaL_dofile(luaState, entry.path().u8string().c_str());
        if(sT != ST_Helper)
          updates.push_back(luabridge::getGlobal(luaState, "update"));
        if(sT == ST_UiPanel){
          // Read init function
          inits.push_back(luabridge::getGlobal(luaState, "init"));
        }
       
    }
    if(renderMan){
      printf("RenderMAN Found\n");
      renderManGlob = std::unique_ptr<Renderer>(renderMan);
    }
    if(sT == ST_UiPanel){
      this->uiMan = uiMan;
      // wow so cool (swag)
      uiManGlob = std::unique_ptr<UIManager>(uiMan);
      runInits();
    }
    
  } 
  void runUpdates(){
    for(luabridge::LuaRef &ref : updates){
      // Execute the update function
      ref(); // pass in args based on the script type (later)
    }
  }


  void exposeUI(){
      // Expose text 
      luabridge::getGlobalNamespace(luaState)
        .beginClass<Text>("Text")
        .addConstructor<void(*) (std::string, int, int)>()
        .addProperty("text", &Text::getText, &Text::setText)
        .addProperty("x", &Text::getX, &Text::setX)
        .addProperty("y", &Text::getY, &Text::setY)
        .endClass();

      // Expose button
      luabridge::getGlobalNamespace(luaState)
        .beginClass<Lua_Button>("Button")
        .addConstructor<void(*) (std::string, int, int, std::string)>()
        .addProperty("text", &Lua_Button::getText, &Lua_Button::setText)
        .addProperty("x", &Lua_Button::getX, &Lua_Button::setX)
        .addProperty("y", &Lua_Button::getY, &Lua_Button::setY)
        .addProperty("luaOnClick", &Lua_Button::getluaOnClick, &Lua_Button::setluaOnClick)
        .endClass();

      // Expose UI
      luabridge::getGlobalNamespace(luaState)
        .beginClass<UI>("UI")
        .addConstructor<void(*) (std::string, int, int, int, int, int, bool)>()
        .addProperty("title", &UI::getTitle, &UI::setTitle)
        .addProperty("index", &UI::getIndex, &UI::setIndex)
        .addProperty("width", &UI::getWidth, &UI::setWidth)
        .addProperty("height", &UI::getHeight, &UI::setHeight)
        .addProperty("visible", &UI::getVisible, &UI::setVisible)
        .addProperty("x", &UI::getX, &UI::setX)
        .addProperty("y", &UI::getY, &UI::setY)
        .addFunction("addText", &UI::addText)
        .addFunction("addButton", &UI::addButton)
        .endClass();
  }

  // Expose UI Utility functions
  void exposeGameUIBackend(){
    luabridge::getGlobalNamespace(luaState)
        .beginClass<UIManager>("UIManager")
        .addConstructor<void(*) (int)>()
        .addFunction("getPanel", &UIManager::getPanel)
        .addFunction("setPanel", &UIManager::setPanel)
        .endClass();

    
    luabridge::setGlobal(luaState, uiManGlob.get(), "UIManager");

  }

  // Expose Graphics Utility functions
  void exposeGameGraphicsBackend(){
    printf("[ScriptManager] Expose Graphics backend\n");
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Renderer>("Graphics")
        .addConstructor<void(*) (int)>()
        .addFunction("getMouseX", &Renderer::getMouseX)
        .addFunction("getMouseY", &Renderer::getMouseY)
        .addFunction("isMouseDown", &Renderer::isMouseDown)
        .endClass();

  
    luabridge::setGlobal(luaState, renderManGlob.get(), "Graphics");
  }

  /*
    Runs the init functions for
    script types that require them
  */
  void runInits(){
    // UI panel init functions (each script mode is seperated so scripts only know the 
    // information they need to know) (wow)
    if(sT == ST_UiPanel){

        exposeUI();
        exposeGameUIBackend();
        exposeGameGraphicsBackend();
      
        int c = 0;
        for(luabridge::LuaRef &ref : inits){
          // Execute the init function
          UI res1 = ref(c);
          // Add the panel
          uiMan->addUIPanel(res1);
          c++;
        }
    }
    // unnesseary, i we now just expose all helper
    // funcs to lUA 
    if(sT == ST_Helper){
      // Expose all C++ lua functions to 
      // the scripts (including classes)

      exposeUI();
      exposeGameUIBackend();
    }
  }
};

/*
  Class for holding a single script
*/
template <typename T, typename ... Ts>
class SingleScriptManager{
private:
luabridge::LuaRef* function;
lua_State* luaState;
public:
  SingleScriptManager(std::string path, std::string functionName){
    int scriptLoadStatus = luaL_dofile(luaState, path.c_str());
    function = luabridge::getGlobal(luaState, functionName.c_str());
    if(!function){
      printf("[SingleScriptManager] Function %s does not exist in %s\n", functionName.c_str(), path.c_str());
      exit(-1);
    }
  } 

  // Exceute a function 
  T execFunction(Ts... args){
    return function(args...);
  }
  
};
#endif