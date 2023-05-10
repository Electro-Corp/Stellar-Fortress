Game::Game(std::string data, std::string config){
  this->data = data;
  this->config = config;
  load();
}
void Game::load(){
  JsonReader iJ(data.c_str());
  JsonReader cJ(config.c_str());
  // read configuration data
  Json::Value configJson = cJ.read();
  this->width = configJson["GameWidth"].asInt();
  this->height = configJson["GameHeight"].asInt();
  loadingMenu("Loading from info.json..");
  Json::Value infoJson   = iJ.read();  
  loadingMenu("Loading teams...");
}
void Game::loadingMenu(std::string info){
  printf("\033[2J");
  printf("\033[%d;%dH",0, 0);
  printf("STELLAR FORTRESS IS LOADING");
  printf("\033[%d;%dH",height, 0);
  printf("%s\n",info.c_str());
}
int Game::gameplay_loop() {
  return 0;
}