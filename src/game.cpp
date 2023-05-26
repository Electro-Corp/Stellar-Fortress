  #include "render/renderImage.h"
#include <filesystem>
#include "settings.h"
#include <iostream>
#include <cstdlib>
#include "system/utils/PerlinNoise.hpp"
#include "system/utils/rgb.h"
#include <limits>

namespace fs = std::filesystem;


// #define DEBUG 1
#define VIEW_MAP 1

double scaleValue(double value, double inputMin, double inputMax, double outputMin, double outputMax);

static double inverseLerp(double xx, double yy, double value);
std::string lastImagePath = "NO_FILE_LOADED_YET";

Game::Game(const std::string& data, const std::string& config, Settings& settings){
  this->data = data;
  this->config = config;
  this->settings = settings;
  load(); 
}

// Look at the loading section in the design notes
void Game::load(){
  JsonReader iJ(data.c_str());
  JsonReader cJ(config.c_str());
  // read configuration data
  Json::Value configJson = cJ.read();
  // Gonna Move these to the passed in settings so that the player can decide -
  this->height = std::stoi(settings.get("height").c_str());
  this->width = std::stoi(settings.get("width").c_str()); // 
  
  // loadingMenu(settings.get("height"), "NO_FILE_LOADED_YET");
  // #ifdef DEBUG
  // getchar();
  // #endif
  // hy idk why no work
  // the old version worked
  // ya and this is better is it tho
  // I do better
  // --------------------------------------------------------------------------
  
  Json::Value infoJson   = iJ.read();
  std::string loadFPath = "game/" + infoJson["LoadingImages"].asString();
  printf("\033[2J");
  printf("\033[%d;%dH",0, 0);
  printf("STELLAR FORTRESS IS LOADING");
 // while(1)
  loadingMenu("Loading teams...",loadFPath);

  
  std::string teamFilePath = "game/" + infoJson["Team_Dir"].asString();
  // now we need to go through every file
  for (const auto & entry : fs::directory_iterator(teamFilePath)){
      std::string g = std::string("Loading ")+ std::string{entry.path().u8string()};
      loadingMenu(g,loadFPath);
      teams.push_back(Team(std::string{entry.path().u8string()}));
  }
  // teams have been loaded, start loading systems


  loadingMenu("Loading systems...", loadFPath);
  std::string systemFilePath = "game/" + infoJson["Systems_Dir"].asString();
  Json::Value systems = infoJson["Systems"];

  for (int i = 0; i < systems.size(); i++) {   
    if(!fs::is_directory(systemFilePath + "/"+ systems[i].asString())) {
      // for(int j=0; j<10; j++) { 
        std::string g = systemFilePath + "/" + systems[i].asString();
        loadingMenu(g,loadFPath);
        this->systems.push_back(System(g));
      
        #ifdef DEBUG
          getchar();
        #endif
     // }
    } else{
      loadingMenu("Fatal ERROR, there was in fact, not a file at " + systemFilePath +"/"+ systems[i].asString(),loadFPath);
    }
  }

  // Perlin Noise Generation Settings and stuff
  generate_terrain_types();
  this->noiseM = generateNoise();
  this->colorM = generate_colors();
  this->map = generate_map();
  
  Window win(settings.get("Name").c_str(), configJson["width"].asInt(), configJson["height"].asInt(), 0, 0);
  system("clear");
  win.RenderMap(this->map);

  #ifdef VIEW_MAP
    getchar();
  #endif
}


void Game::loadingMenu(std::string info, std::string loadFPath){
  // add terminal image renderer? (by me)
  if(loadFPath != lastImagePath){
    renderImage(loadFPath.c_str(),0,1);
    lastImagePath = loadFPath;
  } //else { // You dont have enough images for this to make sense
    // renderImage(loadFPath.c_str(),0,1);
  // }
  printf("\033[%d;%dH",height, 0);
  printf("%s\n",info.c_str());
  #ifdef DEBUG
  getchar();
  #endif
}

// Make more better
RGB Game::make_color_grey(const RGB& rgb, double scale_factor) {
    // Calculate the average of the color channels
    scale_factor = std::max(0.0, std::min(scale_factor, 4.0));
    double grey = (rgb.r + rgb.g + rgb.b) / 3.0;

    double color_amount = 1.0 - scale_factor / 4.0;
    
    // Calculate the new color channels
    double new_red = rgb.r * color_amount + grey * (1.0 - color_amount);
    double new_green = rgb.g * color_amount + grey * (1.0 - color_amount);
    double new_blue = rgb.b * color_amount + grey * (1.0 - color_amount);
    
    return RGB
      (new_red, new_green, new_blue);
}

std::vector<std::vector<double>> Game::generateNoise() {
  std::vector<std::vector<double>> noiseMap;
  
  const double scale = 1;
  const int octaves = 2;    
  const double persistance = 1.2;  // Random value rn
  const double lacunarity = 1.3; // Random value rn

  double minValue = std::numeric_limits<double>::lowest();
  double maxValue = std::numeric_limits<double>::max();
  
  siv::PerlinNoise::seed_type seed;

  if(this->settings.get("seed").compare("") != 0) {
     seed = std::stoi(settings.get("seed"));
  } else {
      srand((unsigned) time(NULL));
      seed = rand();
  }  
  
  const siv::PerlinNoise perlin{ seed };
  
  
  for (std::int32_t y = 0; y < this->height; ++y) {
    std::vector<double> l; noiseMap.push_back(l);
			for (std::int32_t x = 0; x < this->width; ++x) {

         double amplitude = 1;
        double frequency = 4;  
        double noiseHeight = 0;

        double halfW = this->width/2;
        double halfH = this->height/2;
        
        /*
        for(int i=0; i < octaves; ++i) {
          double sampleX = (x-halfW) / scale * frequency;
          double sampleY = (y-halfH) / scale * frequency;

          double perlinVal = perlin.noise2D_01(sampleX, sampleY); // Returns range [-1,1]
          noiseHeight += perlinVal * amplitude;

          amplitude *= persistance;
          frequency *= lacunarity;
        } 
        */
        
        noiseHeight = perlin.noise2D_01(y, x);
        
        if(noiseHeight > maxValue) {
          maxValue = noiseHeight;
        } else if (noiseHeight < minValue) {
          minValue = noiseHeight;
        }
        
        noiseMap[y].push_back(noiseHeight);
			}
		}
    for (std::int32_t y = 0; y < this->height; ++y) {
			for (std::int32_t x = 0; x < this->width; ++x) {
        // std::cout << minValue << " " << maxValue << " " << noiseMap[y][x] << std::endl; 
        // std::cout << noiseMap[y][x] << std::endl;
        // This does bad \/
        // noiseMap[y][x] = inverseLerp(minValue, maxValue, noiseMap[y][x]);
        // std::cout << noiseMap[y][x];
        // std::cout << maxValue << " ";
        // This does bad \/
        // noiseMap[y][x] = (noiseMap[y][x] - minValue) / (maxValue - minValue);
        //  noiseMap[y][x] = noiseMap[y][x];
        // std::cout << noiseMap[y][x];

        // Same as other ones
        // Idk why but this makes the number 0 
        // noiseMap[y][x] = scaleValue(noiseMap[y][x], minValue, maxValue, 0, 5);
      }
    }
  return noiseMap;
}

/* BACKUP
void Game::GenerateNoise() {
  const double frequency = 4; // Idk this value can be messed with. Range - [0.1 .. 64.0]
  const std::int32_t octaves = 2; // Same. Range - [1 .. 16] // could let the player mess with these
  siv::PerlinNoise::seed_type seed; // Range - [0 .. 2^32-1]

  
  if(this->settings.get("seed").compare("") != 0) {
     seed = std::stoi(settings.get("seed"));
  } else {
    srand((unsigned) time(NULL));
    seed = rand();
  }

  
  const siv::PerlinNoise perlin{ seed };
  
  const double fx = (frequency / this->width);
	const double fy = (frequency / this->height);

  for (std::int32_t y = 0; y < this->height; ++y) {
      // std::vector<Tile> l;
      // this->map.push_back(l);
			for (std::int32_t x = 0; x < this->width; ++x) {
				
        double height = perlin.octave2D_01((x * fx), (y * fy), octaves) * 5;

        RGB color(100, 175, 80);
        color = make_color_grey(color,  pow(height,1.2) );  

        
        
        Tile t(color, x, y, height);
        this->map[y].push_back(t);
			}
		}

  #ifdef DEBUG
  getchar();
  #endif
}
*/


std::vector<std::vector<RGB>> Game::generate_colors() {
  std::vector<std::vector<RGB>> colorMap;
  for(int y = 0; y < this->height; ++y) {
    std::vector<RGB> l; colorMap.push_back(l);
    for(int x = 0; x < this->width; ++x) {
      double cur_height = this->noiseM[y][x];
      for(int i=0;i < regions.size(); ++i) {
        if(cur_height <= regions[i].height) { // Im doing something right if it goes wrong
          colorMap[y].push_back(regions[i].color); // why it blue (is it supposed to be (blu))
          break;
        }
      }
    }
  }
  return colorMap;
 }

void Game::generate_terrain_types() {
  // RGB dw(0, 100, 255);
  // TerrainType deep_water("deep_water", .1, dw);
  // regions.push_back(deep_water);
  
  RGB sw(100, 155, 255);
  TerrainType shallow_water("shallow_water", .3, sw);
  regions.push_back(shallow_water);

  RGB be(220, 220, 60);
  TerrainType beach("beach", .4, be);
  regions.push_back(beach);

  RGB gr(150, 220, 75);
  TerrainType plain("plain", .75, gr);
  regions.push_back(plain);

  // RGB hi(130, 180, 80);
  // TerrainType hill("hill", .85, hi);
  // regions.push_back(hill);

  // RGB mtb(90, 70, 70);
  // TerrainType bottom_mt("bottom_mt", .9, mtb);
  // regions.push_back(bottom_mt);

  // RGB mt(70, 56, 56);
  // TerrainType mount("mt", .95, mt);
  // regions.push_back(mount);

  // RGB pk(225, 225, 225);
  // TerrainType peak("peak", 1, pk);
  // regions.push_back(peak);
}

std::vector<std::vector<Tile>> Game::generate_map() {
  std::vector<std::vector<Tile>> m;
  for(int y = 0; y < this->height; ++y) {
    std::vector<Tile> l; m.push_back(l);
    for(int x = 0; x < this->width; ++x) {
      Tile f(colorM[y][x], x, y, noiseM[y][x]);
      m[y].push_back(f);
    }
  }
  return(m);
}

double inverseLerp(double start, double end, double value) {
  return (value - start)/(end - start);
}

double scaleValue(double value, double inputMin, double inputMax, double outputMin, double outputMax) {
    double scaledValue = (value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin;
    return scaledValue;
}