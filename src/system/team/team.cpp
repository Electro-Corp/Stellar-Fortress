Team::Team(std::string t) {
  this->name = t;
  std::string loc = std::string(t);
  this->TeamJson = JsonReader(loc).read();
  this->Government = TeamJson["Government"].asString(); 
  this->StartMoney = TeamJson["StartMoney"].asInt();
  this->Population = TeamJson["Population"].asInt();
  this->workCond = TeamJson["WorkCond"].asInt();
}

std::string Team::getTeam() {
  return this->name;
}

void Team::AddHuman(Human Person){
  Humans.push_back(Person);
}

/*int Team::getWorkC() {
  return this->WorkCond;
}*/
