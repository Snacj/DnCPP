#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <vector>

#include "../utils/globals.h"
#include "entity.h"

class Player: public Entity
{
private:
    // player stats

public:
    Player();

    void loadSprites() override;
    void setup() override;
    void update() override;
};

#endif
