#ifndef READJSON_H
#define READJSON_H
#include <json/value.h>
#include <json/json.h>
#include <fstream>
class JsonReader{
public:
  char* name;
  JsonReader(char* fileName){
    this->name = fileName;
  }
  /*
    How to use JSON Reader
    It will return a var (crazy)
    To get value use var["KeyName"]
    so if json look like
    {
      "goof": 3
    }
    u use varName["goof"]
  */
  Json::Value read(){
    std::ifstream f(this->name);
    Json::Value v;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    parseFromStream(builder, f, &v, &errs);
    return v;
  }
};
#endif