#ifndef NOISE_H
#define NOISE_H

class Noise {
  std::vector<std::vector<double>> Noise::generateNoise() {
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
          
          /* OCTAVES
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
          /* Attempt to Normalize, Fails*/
          // noiseMap[y][x] = (noiseMap[y][x] - minValue) / (maxValue - minValue);
        }
      }
    return noiseMap;
  }
}