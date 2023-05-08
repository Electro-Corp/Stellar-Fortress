/*
  The sector defines areas of map, optimizing the game so it dosent
  run at like 8 fps
*/
#ifndef SECTOR_H
#define SECTOR_H
class Sector{
  private:
    int Secx, Secy, CPS;
    std::vector<std::vector<int>> SecCord;s
    std::vector<GameObject> gameObs;
  public:
    Sector(int, int);
};
#include "sector.cpp"
#endif