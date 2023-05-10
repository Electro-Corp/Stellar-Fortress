
Team::Team(std::string t) {
  this->name = t;
  this->TeamJson = JsonReader(t + ".json");
  this->Government = TeamJson["Government"].asString(); 
  this->StartMoney = TeamJson["StartMoney"].asInt();
  this->Population = TeamJson["Population"].asInt();
  this->WorkCond = TeamJson["WorkCond"].asInt();
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
