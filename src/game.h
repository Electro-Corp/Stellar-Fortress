#ifndef GAME_H
#define GAME_H
class Game {

  public:
    Game(std::string);
    int gameplay_loop();
  
  private:
  protected:
    std::string data;
};
#endif