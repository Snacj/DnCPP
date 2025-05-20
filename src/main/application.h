#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <thread>

#include "../entities/player.h"


class Application
{
private:
    void update();
    void draw();

    std::thread gameThread;
    int gameState;

public:
    Application();

    Player& getPlayer();
    void setup();
    void run();
};

#endif
