/*
  SF_SCRIPT
*/
#ifndef FUNCTION_H
#define FUNCTION_H
class Function{
private:
std::string name;
std::vector<std::string> code;
public:
  Function(std::string name, std::vector<std::string> code){
    this->name = name;
    this->code = code;
  }
};
#endif