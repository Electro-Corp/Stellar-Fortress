#ifndef VAR_H
#define VAR_H

enum varType {   
    type = 0, 
    intVal = 1, 
    stringVal = 2,
    floatVal = 3
};

class Variable{
public:
std::string name, value, scope;
int varType;
Variable(std::string name, std::string value, int varType, std::string scope){
  this->name = name;
  this->value = value;
  this->varType = varType;
}

};
#endif