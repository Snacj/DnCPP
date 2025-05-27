#include <SDL2/SDL.h>

#include "../utils/globals.h"
#include "entity.h"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::draw()

{
    if(screenX + TILE_SIZE > 0 &&
       screenX < SCREEN_WIDTH &&
       screenY + TILE_SIZE > 0 &&
       screenY < SCREEN_HEIGHT) {

        SDL_RenderCopy(gRenderer, texture, NULL, &rect);
        // DEBUG
        if (debug) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x10);
            SDL_RenderFillRect(gRenderer, &debugSolidArea);
       }
    }
}

