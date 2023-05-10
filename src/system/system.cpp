System::System(std::string loadFromFile){
  // Create system
  JsonReader systemJson(loadFromFile);
  Json::Value out = systemJson.read();
}