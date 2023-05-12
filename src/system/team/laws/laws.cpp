Laws::Laws(char* name, char* lawTeam){
  this->name = name;
  if(team == null){
    std::string loc = "UniLaws.Json";
  }else{
    std::string loc = std::string(lawTeam) + (char*)"Laws.json";
  }
  this->LawJson = JsonReader(loc).read();
  /*
  this->Government = LawJson["Government"].asString(); 
  this->StartMoney = LawJson["StartMoney"].asInt();
  this->Population = LawJson["Population"].asInt();
  this->workCond = LawJson["WorkCond"].asInt();*/
  for (auto const& id : LawJson.getMemberNames()) {
    variables[id] = LawJson[id].asInt();
  }
}
