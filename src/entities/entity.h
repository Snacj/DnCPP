#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <vector>

#include "../utils/globals.h"

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
};

class Entity
{
protected:

    // animation
    int animationTimer;
    int currentAnimationFrame;
    bool idle;

    // DEBUG
    bool debug;

    // texutre
    std::vector<SDL_Texture*> textures;
    SDL_Texture* texture;

    // entity
    SDL_Rect rect;
    SDL_Rect debugSolidArea;


public:
    virtual void loadSprites();
    virtual void setup();
    virtual void update();
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
