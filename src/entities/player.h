#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <vector>

#include "../utils/globals.h"

class Player
{
private:
    // speed
    int speed;

    // animation
    int animationTimer;
    int currentAnimationFrame;
    int direction;
    bool idle;

    // DEBUG
    bool debug;

    // texture
    std::vector<SDL_Texture*> textures;
    SDL_Texture* texture;

    // Player
    SDL_Rect rect;
    SDL_Rect solidArea;

public:
    Player();

    void loadSprites();
    void setup();
    void update();
    void draw();

    // position
    int worldX, worldY;
    int screenX, screenY;
};

#endif
