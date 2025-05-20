#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>

#include "application.h"
#include "../tiles/tilemanager.h"
#include "../utils/globals.h"
#include "../entities/player.h"

TileManager tileManager;
Player player;

enum gameState {
    MENU,
    GAME,
};

Application::Application()
{

}

void Application::setup()
{
    // Setup Textures
    player.loadSprites();
    player.setup();
    tileManager.loadMap("assets/maps/map.txt");
    tileManager.loadSprites();
    gameState = GAME;
}

void Application::run()
{
    // Running Flag
    bool quit = false;

    // Event Handler
    SDL_Event e;

    // Main gameloop
    while( !quit )
    {
        // This has to be first
        Uint32 frameStart = SDL_GetTicks();
        // Handle all events in queue
        while( SDL_PollEvent( &e ) != 0)
        {
            // Allows the user to quit
            if ( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }
        update();
        draw();
        // This has to be last
        // 60 FPS
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000/60) SDL_Delay(1000/60 - frameTime);
    }
}

void Application::update()
{
    player.update();
}

void Application::draw()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);

    if(gameState == GAME) {
        tileManager.drawTiles();
        player.draw();
    } else if(gameState == MENU) {

    } 

    SDL_RenderPresent(gRenderer);
}
