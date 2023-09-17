#include "planet.h"
#include "terraintypes/terrainreqs.h"

Planet::Planet(std::string dir) {
  JsonReader json(dir);
  Json::Value p = json.read();

  this->name = p["Name"].asString();

  this->sizex = p["MapDimensions"][0].asInt();
  this->sizey = p["MapDimensions"][1].asInt();

  int enum_val = 0;
  for (auto i : p["Regions"]) {
    r_enum[i["biome"].asString()] = enum_val;
    c_enum[enum_val] = RGB(i["color"]["red"].asInt(), i["color"]["blue"].asInt(), i["color"]["green"].asInt());
    h_enum[enum_val] = HHH(i["requires"]["height"].asInt(), i["requires"]["heat"].asInt(), i["requires"]["humidity"].asInt());
    ++enum_val;
  }
  
  // 4 is a test value
  this->pMap = PlanetMap(this->sizex, this->sizey, r_enum, c_enum, h_enum, 4);
}

PlanetMap* Planet::get_map() {
  return &(this->pMap);
}