#include <string>
#include <vector>
#include <sstream> 
#include <algorithm> // make it generate less omg it takes 5  minutes to load
#include "variable.h" // Its in the jsonsuyghjgjghjgjyuthjgtjhgj may god be with you :pray: inshallah we shall fix this bug     thanks omar
#include "function.h"
#include "../system/planet/gameObject.h"
#ifndef SCRIPT_H
#define SCRIPT_H
#define DEBUG

//typedef vector<tuple<int, int, std::string>> doubleTuple;

bool iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

//#define SCRIPT_VAR_DEBUG
std::string dataTypes[] = {"type", "int", "string", "float"};
class Script{
private:
std::vector<Variable> vars;
std::vector<Function> functions; 
  //doubleTuple functionWhere; 
public:


  Script(std::stringstream* data){
    // split
    std::string segment;
    std::vector<std::string> seglist;  
    while(std::getline(*data, segment, '\n')){
       if(segment != "")
        seglist.push_back(segment);
    }
    printf("Parsing Variables..\n");
    // parse
    parseVars(seglist);
    parseFunctions(seglist);
#ifdef DEBUG
    debug();
#endif


    // init 
    
    
  }

  /*
    Functions for variables
  */
  void parseVars(std::vector<std::string> seglist){
    // get vars
    for(int i = 0; i < seglist.size(); i++){
      std::string TMPsegment;
      std::vector<std::string> line;
      std::stringstream tmp(seglist[i]);
      while(std::getline(tmp, TMPsegment, ' ')){
         line.push_back(TMPsegment);
      }
      #ifdef SCRIPT_VAR_DEBUG
      printf("Check against defined datatypes..\n");
      #endif
      // check against data type
      for(int i = 0; i < sizeof(dataTypes)/sizeof(dataTypes[0]); i++){
        if(line[0].find(dataTypes[i]) != std::string::npos){
          addVar(line, i);
        }
      }
      
    }  
  }
  void addVar(std::vector<std::string> line, int num){
    #ifdef SCRIPT_VAR_DEBUG
    printf("Adding Variable..\n");
    #endif
    std::string varName = line[1], value;
    // check against other vars
    for(int i = 0; i < vars.size(); i++){
      if(vars[i].name == line[2]){
        if(vars[i].varType == num)
          value = vars[i].value;
        else{
          printf("Conversion from [%s to %s] not permitted\n", dataTypes[vars[i].varType].c_str(), dataTypes[num].c_str());
          exit(-1);        
        }
      }
    }
    if(value == ""){
      switch(num){
        case 2:
        value = line[2];
        break;

        // most things dont have spaces
        default:
        value = line[2];
        break;
      }
    }
    vars.push_back(Variable(varName, value, num, "global")); // set to global
  }

  /*
    Functions for functions (inception)
  */
  void parseFunctions(std::vector<std::string> seglist){
    // check each line
    for(int i = 0; i < seglist.size(); i++){
      std::string TMPsegment;
      
      std::vector<std::string> line;
      std::stringstream tmp(seglist[i]);
      while(std::getline(tmp, TMPsegment, ' ')){
         line.push_back(TMPsegment);
      }

      /*
        steps:
        1. check for function
        2. check if script type has that function
        3. if so load
      */
      
      if(line[0].find("function") != std::string::npos){
        // wow function 
        // Find the namespace
        std::string funcType = line[1];
        std::string funcName = line[2];
        std::vector<std::string> code;
        // Unit?
        if(iequals(funcType, "unit")){
          // cool check if there is a override for it
          
          for(int c = i; c < seglist.size(); c++){
            if(seglist[c].find("}") != std::string::npos) break;
            code.push_back(seglist[c]);
          }
          Function tmp = Function(funcName, code);
          functions.push_back(tmp);
        }

        std::cout << "> FUNCTION < Name: " << funcName << " of type " << funcType << "\n";
        for(int j = 0; j < code.size(); j++){
          std::cout << code[j] << "\n";
        }
        
      }
      
    }
  }


  void debug(){
    printf("Vars: \n");
    for(int i = 0; i < vars.size(); i++){
      std::cout << vars[i].name << " = " << vars[i].value << "\n";
    }
  }


  void executeFunction(int index){
    // Start 
  }


};
#endif