#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <vector>

#include "../utils/globals.h"

enum direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    UP_LEFT = 4,
    UP_RIGHT = 5,
    DOWN_LEFT = 6,
    DOWN_RIGHT = 7,
};

class Entity
{
protected:

    // animation
    int animationTimer;
    int currentAnimationFrame;
    bool idle;

    int walkingDirectionTimer = 0;

    // DEBUG
    bool debug;

    // texutre
    std::vector<std::string> texture_path;
    std::vector<SDL_Texture*> textures;
    SDL_Texture* texture;

    // entity
    SDL_Rect rect;
    SDL_Rect debugSolidArea;


public:
    Entity();
    virtual ~Entity();

    virtual void loadSprites() = 0;
    virtual void setup() = 0;
    virtual void update() = 0;
    void draw();

    std::string name = "";

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
