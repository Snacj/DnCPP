#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include "../utils/globals.h"
#include "entity.h"

class Npc: public Entity
{
private:
    // entity stats, texts etc.

public:
    Npc();

    void loadSprites() override;
    void setup() override;
    void update () override;

    // speed
    int speed;

    //position
    int wordlX, worldY;
    int screenX, screenY;

    int direction;

    // collision
    bool collisionOn;
    SDL_Rect solidArea;
};

#endif
