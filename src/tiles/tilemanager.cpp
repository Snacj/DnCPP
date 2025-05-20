#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/globals.h"
#include "../utils/textureLoader.h"
#include "../main/application.h"
#include "tilemanager.h"

Application app;

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
    tiles.push_back("tree");

    textures = tl.loadMedia(tiles);

}

void TileManager::drawTiles() {
    int worldCol = 0;
    int worldRow = 0;
    SDL_Rect destRect;
    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;

    while (worldCol < MAX_WORLD_COL && worldRow < MAX_WORLD_ROW) {
        int tileNum = map[worldCol][worldRow];
        int worldX = worldCol * TILE_SIZE;
        int worldY = worldRow * TILE_SIZE;
        int screenX = worldX - app.getPlayer().worldX + app.getPlayer().screenX;
        int screenY = worldY - app.getPlayer().worldY + app.getPlayer().screenY;

        if(worldX + TILE_SIZE > app.getPlayer().worldX - app.getPlayer().screenX &&
            worldX - TILE_SIZE < app.getPlayer().worldX + app.getPlayer().screenX &&
            worldY + TILE_SIZE > app.getPlayer().worldY - app.getPlayer().screenY &&
            worldY - TILE_SIZE < app.getPlayer().worldY + app.getPlayer().screenY)
        {
            destRect.x = screenX;
            destRect.y = screenY;
            SDL_RenderCopy(gRenderer, textures[tileNum], NULL, &destRect);
            
        }

        worldCol++;
        if (worldCol == MAX_WORLD_COL) {
            worldCol = 0;
            worldRow++;
        }

    }


    //for (size_t i = 0; i < map.size(); i++) {
    //    for (size_t j = 0; j < map[i].size(); j++) {
    //        SDL_Rect destRect = { (int)i * TILE_SIZE, (int)j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    //        SDL_RenderCopy(gRenderer, textures[map[i][j]], NULL, &destRect);
    //    }
    //}
}

