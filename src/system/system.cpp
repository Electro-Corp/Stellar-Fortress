System::System(std::string loadFromFile){
  // Create system
  JsonReader systemJson(loadFromFile);  
  Json::Value out = systemJson.read();

  // stores the directory of planets relative to the folder "game"
  Json::Value planetDir = out["Planets"];
  Logger l("System");
  for(int i = 0; i < planetDir.size()-1; ++i) {

    size_t lastSlashIndex = loadFromFile.find_last_of('/');
    std::string result;
    if (lastSlashIndex != std::string::npos) {
        result = loadFromFile.substr(0, lastSlashIndex+1);
    }

    std::string dir = result + "planets/" +  planetDir[i].asString() + ".json";
    l.log("constructor", dir);
 
    Planet p(dir);
    p.init();
    planets.push_back(p);
  }
}  

class PlanetOutOFRangeExecption : public std::exception {
    public:
char * what () {
        return "Planet Index out of range";
    }
};


Planet System::get_planet(int i) {
  if(i < planets.size())
    return planets[i];
  else
    throw PlanetOutOFRangeExecption();
}