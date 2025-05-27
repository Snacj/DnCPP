#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <vector>

#include "../utils/globals.h"
#include "entity.h"

class Player: public Entity {
private:

    // animation
    int animationTimer;
    int currentAnimationFrame;
    bool idle;

    // DEBUG
    bool debug;

    // texture
    std::vector<SDL_Texture*> textures;
    SDL_Texture* texture;

    // Player
    SDL_Rect rect;
    SDL_Rect debugSolidArea;

public:
    Player();

    void loadSprites() override;
    void setup() override;
    void update() override;
    void draw();

    // speed
    int speed;

    // position
    int worldX, worldY;
    int screenX, screenY;

    int direction;

    // collision
    bool collisionOn;
    SDL_Rect solidArea;
};

#endif
