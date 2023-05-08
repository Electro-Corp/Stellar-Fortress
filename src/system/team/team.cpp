
Team::Team(std::string t) {
  this->name = t;
  this->TeamJson = JsonReader(t + ".json");
  this->Government = Team["Government"].asString(); 
  this->StartMoney = Team["StartMoney"].asInt();
  this->Population = Team["Population"].asInt();
  this->WorkCond = Team["WorkCond"].asInt();
}

Team::Team(char* t) {
  this->name = t.c_str();
  this->TeamJson = JsonReader(t + ".json");
  this->Government = Team["Government"].asString();
  this->StartMoney = Team["StartMoney"].asInt();
  this->Population = Team["Population"].asInt();
  this->WorkCond = Team["WorkCond"].asInt();
}

char* Team::getTeam() {
  return this->name;
}

void Team::AddHuman(Human Person){
  Humans.push_back(Person);
}

/*int Team::getWorkC() {
  return this->WorkCond;
}*/
