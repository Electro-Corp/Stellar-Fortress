#include "planet.h"
#include "terraintypes/terrainreqs.h"
// #include "../utils/readJson.h"
// Planet::Planet(std::string name, int size) {
//   this->size = size;
//   
//   l.log("PlanetCpp", "Const");
//   init();
// }

Planet::Planet(std::string dir) {
  Logger l("planet");
  
  l.log("System.constructor", "reading json");
  
  JsonReader json(dir);
  Json::Value p = json.read();

  l.log("planet.constructor", "reading name");
  this->name = p["Name"].asString();

  l.log("planet.constructor", "reading map dimensions");
  this->sizex = p["MapDimensions"][0].asInt();
  this->sizey = p["MapDimensions"][1].asInt();

  for (auto i : p["Regions"]) {
    RGB color(i[2][0].asInt(), i[2][1].asInt(), i[2][2].asInt());
    TerrainType r(i[0].asString(), i[1].asDouble(), color);
    this->regions.push_back(r);
  }
}
  
int Planet::init() {
    generate_terrain_types();
    Logger l("test1");
    l.log("PlanetCpp", "Init");

    std::vector<TerrainReq> lmm;
    TerrainReq f("peak", "mt", 4);
    lmm.push_back(f);
  
    PlanetMap m(this->sizex, this->sizey, this->regions, lmm);
    this->pMap = m;
    return 0;
}



// Obviously change this to use the planet json at somepoint no (fuck modding)
void Planet::generate_terrain_types() {
  RGB dw(0, 100, 255);
  TerrainType deep_water("deep_water", .1, dw);
  this->regions.push_back(deep_water);
  
  RGB sw(100, 155, 255);
  TerrainType shallow_water("shallow_water", .3, sw);
  this->regions.push_back(shallow_water);

  RGB be(220, 220, 60);
  TerrainType beach("beach", .4, be);
  this->regions.push_back(beach);

  RGB gr(150, 220, 75);
  TerrainType plain("plain", .75, gr);
  this->regions.push_back(plain);

  RGB hi(130, 180, 80);
  TerrainType hill("hill", .85, hi);
  this->regions.push_back(hill);

  RGB mtb(90, 70, 70);
  TerrainType bottom_mt("bottom_mt", .9, mtb);
  this->regions.push_back(bottom_mt);

  RGB mt(70, 56, 56);
  TerrainType mount("mt", .95, mt);
  this->regions.push_back(mount);

  RGB pk(225, 225, 225);
  TerrainType peak("peak", 1, pk);
  this->regions.push_back(peak);
}

PlanetMap* Planet::get_map() {
  return &(this->pMap);
}