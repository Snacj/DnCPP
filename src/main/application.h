#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <thread>

#include "collisionChecker.h"
#include "../entities/player.h"

enum gameState {
    MENU,
    GAME,
};

class Application
{
private:
    void update();
    void draw();

    std::thread gameThread;

public:
    Application();

    Player& getPlayer();
    CollisionChecker& getCollisionChecker();
    void setup();
    void run();

    bool quit;
    int gameState;
};

#endif
