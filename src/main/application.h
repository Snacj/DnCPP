#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <thread>


class Application
{
private:
    void update();
    void draw();

    std::thread gameThread;
    int gameState;

public:
    Application();

    void setup();
    void run();
};

#endif
