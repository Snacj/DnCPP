#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <vector>

#include "../utils/globals.h"
#include "../utils/textureLoader.h"
#include "tilemanager.h"

TileManager::TileManager() {

}

void TileManager::loadSprites()
{
    tiles.push_back("grass");
    tiles.push_back("dirt");
    tiles.push_back("stone");

    textures = tl.loadMedia(tiles);

}

void TileManager::drawTiles() {
    for (int i = 0; i < SCREEN_COLS; i++) {
        for (int j = 0; j < SCREEN_ROWS; j++) {
            SDL_Rect destRect = { i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(gRenderer, textures[0], NULL, &destRect);
        }
    }
}

