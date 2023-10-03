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
  lua_State* m_luaState;
// Vectors to hold all the functions
  std::vector<luabridge::LuaRef> m_updates;
  std::vector<luabridge::LuaRef> m_inits;
  ScriptTypes m_sT;
  UIManager* m_uiMan;
  std::unique_ptr<UIManager> m_uiManGlob;
  std::unique_ptr<Renderer> m_renderManGlob;
public:
  ScriptManager(std::string p_scriptPath, ScriptTypes p_sT, UIManager* p_uiMan = nullptr, Renderer* p_renderMan = nullptr) {
    this->m_sT = p_sT;
    
    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);
    for (const auto & entry : fs::directory_iterator("game/" + p_scriptPath)){
        std::ifstream file(entry.path().u8string());
        int scriptLoadStatus = luaL_dofile(m_luaState, entry.path().u8string().c_str());
        if(m_sT != ST_Helper)
          m_updates.push_back(luabridge::getGlobal(m_luaState, "update"));
        if(m_sT == ST_UiPanel){
          // Read init function
          m_inits.push_back(luabridge::getGlobal(m_luaState, "init"));
        }
       
    }
    if(p_renderMan){
      m_renderManGlob = std::unique_ptr<Renderer>(p_renderMan);
    }
    if(m_sT == ST_UiPanel){
      this->m_uiMan = p_uiMan;
      // wow so cool (swag)
      m_uiManGlob = std::unique_ptr<UIManager>(p_uiMan);
      runm_inits();
    }
    
  } 
  void runUpdates(){
    for(luabridge::LuaRef &ref : m_updates){
      // Execute the update function
      ref(); // pass in args based on the script type (later)
    }
  }


  void exposeUI(){
      // Expose text 
      luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Text>("Text")
        .addConstructor<void(*) (std::string, int, int)>()
        .addProperty("text", &Text::getText, &Text::setText)
        .addProperty("x", &Text::getX, &Text::setX)
        .addProperty("y", &Text::getY, &Text::setY)
        .endClass();

      // Expose button
      luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Lua_Button>("Button")
        .addConstructor<void(*) (std::string, int, int, std::string)>()
        .addProperty("text", &Lua_Button::getText, &Lua_Button::setText)
        .addProperty("x", &Lua_Button::getX, &Lua_Button::setX)
        .addProperty("y", &Lua_Button::getY, &Lua_Button::setY)
        .addProperty("luaOnClick", &Lua_Button::getluaOnClick, &Lua_Button::setluaOnClick)
        .endClass();

      // Expose UI
      luabridge::getGlobalNamespace(m_luaState)
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
        .addFunction("getTexts", &UI::getTexts)
        .addFunction("setText", &UI::setText)
        .addFunction("getText", &UI::getText)
        .addFunction("addButton", &UI::addButton)
        .endClass();
  }

  // Expose UI Utility functions
  void exposeGameUIBackend(){
    luabridge::getGlobalNamespace(m_luaState)
        .beginClass<UIManager>("UIManager")
        .addConstructor<void(*) (int)>()
        .addFunction("getPanel", &UIManager::getPanel)
        .addFunction("setPanel", &UIManager::setPanel)
        .endClass();

    
    luabridge::setGlobal(m_luaState, m_uiManGlob.get(), "UIManager");

  }

  // Expose Graphics Utility functions
  void exposeGameGraphicsBackend(){
    printf("[ScriptManager] Expose Graphics backend\n");
    luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Renderer>("Graphics")
        .addConstructor<void(*) (int)>()
        .addFunction("getMouseX", &Renderer::getMouseX)
        .addFunction("getMouseY", &Renderer::getMouseY)
        .addFunction("isMouseDown", &Renderer::isMouseDown)
        .endClass();

  
    luabridge::setGlobal(m_luaState, m_renderManGlob.get(), "Graphics");
  }

  /*
    Runs the init functions for
    script types that require them
  */
  void runm_inits(){
    // UI panel init functions (each script mode is seperated so scripts only know the 
    // information they need to know) (wow)
    if(m_sT == ST_UiPanel){

        exposeUI();
        exposeGameUIBackend();
        exposeGameGraphicsBackend();
      
        int c = 0;
        for(luabridge::LuaRef &ref : m_inits){
          // Execute the init function
          UI res1 = ref(c);
          // Add the panel
          m_uiMan->addUIPanel(res1);
          c++;
        }
    }
    // unnesseary, i we now just expose all helper
    // funcs to lUA 
    if(m_sT == ST_Helper){
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
luabridge::LuaRef* m_function;
lua_State* m_luaState;
public:
  SingleScriptManager(std::string p_path, std::string p_functionName){
    int scriptLoadStatus = luaL_dofile(m_luaState, p_path.c_str());
    m_function = luabridge::getGlobal(m_luaState, p_functionName.c_str());
    if(!m_function){
      printf("[SingleScriptManager] Function %s does not exist in %s\n", p_functionName.c_str(), p_path.c_str());
      exit(-1);
    }
  } 

  // Exceute a function 
  T execFunction(Ts... args){
    return m_function(args...);
  }
  
};
#endif