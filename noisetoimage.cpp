#include <iostream>
#include <fstream>
#include <vector>
// #include "src/includes.h"

#include "src/system/planet/tile.h"
#include "src/map_generation/planetmap.h"
#include "src/system/system.h"
// Include your Tile class definition

void renderTilesAsImage(std::vector<std::vector<Tile>> tiles, int width, int height, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    // Write the PPM header
    outputFile << "P3" << std::endl;
    outputFile << width << " " << height << std::endl;
    outputFile << "255" << std::endl;

    // Loop through the 2D array of Tile objects and write pixel colors
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const Tile& tile = tiles[y][x];
            int r = static_cast<int>(tile.rgb.r * 255);
            int g = static_cast<int>(tile.rgb.g * 255);
            int b = static_cast<int>(tile.rgb.b * 255);
            outputFile << r << " " << g << " " << b << " ";
        }
        outputFile << std::endl;
    }

    outputFile.close();
}

int main() {
    const int width = 50;
    const int height = 50;

    /*/ Create a 2D array of Tile objects (replace this with your actual data)
    Tile** tiles = new Tile*[height];
    for (int y = 0; y < height; y++) {
        tiles[y] = new Tile[width];
        for (int x = 0; x < width; x++) {
            // Initialize Tile objects with your data
            tiles[y][x] = Tile(/* Initialize with appropriate parameters *//*);
        }
    }*/
    System::System s = new System::System("game/basegame/data/sytems/default/SolarSystem.json");
    
    PlanetMap::PlanetMap pmap = s.get_planet(0).get_map();
    std::vector<std::vector<Tile::Tile>> tiles = pmap.get();
    // Call the rendering function
    renderTilesAsImage(tiles, width, height, "output_image.ppm");

    // Clean up memory
    /* for (int y = 0; y < height; y++) {
        delete[] tiles[y];
    }
    delete[] tiles;

    return 0; */
}
