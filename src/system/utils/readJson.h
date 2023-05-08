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
  #include <json/json.h>
#include <fstream>
#include <iostream>

Json::Value read() {
    std::ifstream f(this->name, std::ifstream::binary);
    if (!f.good()) {
        std::cerr << "Error: Could not open file " << this->name << std::endl;
        exit(EXIT_FAILURE);
    }
    Json::Value v;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false; // ignore comments in JSON file
    std::string errs;

    bool parsingSuccessful = Json::parseFromStream(builder, f, &v, &errs);
    if (!parsingSuccessful) {
        std::cerr << "Error: Failed to parse JSON file " << this->name << std::endl;
        std::cerr << "Parsing errors: " << errs << std::endl;
        exit(EXIT_FAILURE);
    }

    return v;
}

};
#endif