#include <SDL2/SDL.h>

#include "../utils/globals.h"
#include "entity.h"

void Entity::draw()
{
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);
    // DEBUG
    if (debug) {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x10);
        SDL_RenderFillRect(gRenderer, &debugSolidArea);
    }
}

