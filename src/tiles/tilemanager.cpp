#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/globals.h"
#include "../utils/textureLoader.h"
#include "tilemanager.h"

TileManager::TileManager() {

}

void TileManager::loadMap( std::string path ) {

    std::ifstream file(path);

    if (!file.is_open()) printf("Error opening Map file.");

    std::string line;
    while(std::getline(file,line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        std::stringstream ss(line);
        std::string value;

        while(std::getline(ss, value, ',')) {
            if(!value.empty()) {
                row.push_back(std::stoi(value));
            }
        }

        map.push_back(row);
    }

    file.close();

}

void TileManager::loadSprites()
{
    tiles.push_back("grass");
    tiles.push_back("dirt");
    tiles.push_back("stone");

    textures = tl.loadMedia(tiles);

}

void TileManager::drawTiles() {
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            SDL_Rect destRect = { (int)i * TILE_SIZE, (int)j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(gRenderer, textures[map[i][j]], NULL, &destRect);
        }
    }
}

