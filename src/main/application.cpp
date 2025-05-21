#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>

#include "application.h"
#include "../tiles/tilemanager.h"
#include "../entities/player.h"
#include "../ui/ui.h"

TileManager tileManager;
Player player;
UI ui;

Application::Application()
{

}

void Application::setup()
{
    // Setup
    // player
    player.loadSprites();
    player.setup();
    // tileManager
    tileManager.loadSprites();
    tileManager.loadMap("assets/maps/map.txt");
    // ui
    ui.loadSprites();
    ui.createUIElements();

    gameState = GAME;
}

void Application::run()
{
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
            if ( e.type == SDL_QUIT )
                quit = true;
            if ( e.key.keysym.sym == SDLK_ESCAPE )
                gameState = MENU;
            if ( e.key.keysym.sym == SDLK_RETURN )
                gameState = GAME;
            if ( gameState == MENU)
                ui.handleMainMenuEvents(&e);
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
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);

    if(gameState == GAME) {
        tileManager.drawTiles();
        player.draw();
    } else if(gameState == MENU) {
        ui.draw();
    }

    SDL_RenderPresent(gRenderer);
}

Player& Application::getPlayer()
{
    return player;
}
