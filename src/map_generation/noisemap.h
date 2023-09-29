#ifndef NOISEMAP_H
#define NOISEMAP_H

#include <vector>
#include <limits>
#include <ctime>

#include "../other/log.h"
#include "../system/utils/PerlinNoise.hpp"

class NoiseMap {
private:
  std::vector<std::vector<double>> noiseM;
  int width;
  int height;
  int seed;
public:
  NoiseMap(int width, int height, int seed) {
    this->width = width;
    this->height = height;
    this->seed = seed;
    generateNoise();
  }

  std::vector<std::vector<double>> get_map() {
    return noiseM;
  }

  int get_height() {
    return this->height;
  }

  int get_width() {
    return this->width;
  }

  std::vector<std::vector<double>> generateNoise() {
    std::vector<std::vector<double>> noiseMap;

    const double scale = 1;
    const int octaves = 2;
    const double persistance = 1.2;
    const double lacunarity = 1.3;

    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::lowest();

    siv::PerlinNoise::seed_type seed;

    if (this->seed == 0) {
      srand(static_cast<unsigned>(time(NULL)));
      seed = static_cast<siv::PerlinNoise::seed_type>(rand());
    }

    const siv::PerlinNoise perlin{ seed };

    for (int y = 0; y < this->height; ++y) {
      std::vector<double> row;
      for (int x = 0; x < this->width; ++x) {
        double amplitude = 1.0;
        double frequency = 4.0;
        double noiseHeight = 0.0;

        double halfW = this->width / 2.0;
        double halfH = this->height / 2.0;

        for (int i = 0; i < octaves; ++i) {
          double sampleX = (x - halfW) / scale * frequency;
          double sampleY = (y - halfH) / scale * frequency;

          double perlinVal = perlin.noise2D_01(sampleX, sampleY);
          noiseHeight += perlinVal * amplitude;

          amplitude *= persistance;
          frequency *= lacunarity;
        }

        if (noiseHeight > maxValue) {
          maxValue = noiseHeight;
        } else if (noiseHeight < minValue) {
          minValue = noiseHeight;
        }

        row.push_back(noiseHeight);
      }
      noiseMap.push_back(row);
    }
    // Logger l("Noise Normalization");
    for (int y = 0; y < this->height; ++y) {
      for (int x = 0; x < this->width; ++x) {
         /* Attempt to Normalize, Fails*/
          // Logger l;
          // l.log("noise value: " + std::to_string(noiseMap[y][x]));
          // l.log("Normalizer", "min value: " + std::to_string(minValue));
          // l.log("Normalizer", "max value: " + std::to_string(maxValue));
          noiseMap[y][x] = inverseLerp(minValue, maxValue, noiseMap[y][x]);
          // l.log("normalized value: " + std::to_string(noiseMap[y][x]));
          // l.newl();
      }
    }

    this->noiseM = noiseMap;
    return noiseMap;
  }

  double inverseLerp(double start, double end, double value) {
    return (value - start) / (end - start);
  }
};
#endif
