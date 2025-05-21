#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

#include "../utils/globals.h"
#include "../utils/textureLoader.h"
#include "../main/application.h"
#include "ui.h"

Button start_game_button;
Button quit_game_button;

UI::UI()
{

}

void UI::loadSprites()
{
    paths.push_back("background");
    paths.push_back("start_game_new_button");
    paths.push_back("quit_game_new_button");

    textures = tl.loadMedia(paths);
}

void UI::createUIElements()
{
    // background
    background.x = 0;
    background.y = 0;
    background.w = SCREEN_WIDTH;
    background.h = SCREEN_HEIGHT;

    createButtons();
}

void UI::createButtons()
{
    // Start Game Button
    start_game_button.isClicked = false;
    start_game_button.isHovered = false;
    start_game_button.texture = textures[1];
    start_game_button.destRect.w = 96 * 2;
    start_game_button.destRect.h = 32 * 2;
    start_game_button.destRect.x = SCREEN_WIDTH / 2 - (start_game_button.destRect.w / 2);
    start_game_button.destRect.y = SCREEN_HEIGHT / 2 - (start_game_button.destRect.h / 2);
    start_game_button.originalRect = start_game_button.destRect;

    // Quit Game Button
    quit_game_button.isClicked = false;
    quit_game_button.isHovered = false;
    quit_game_button.texture = textures[2];
    quit_game_button.destRect.w = 96 * 2;
    quit_game_button.destRect.h = 32 * 2;
    quit_game_button.destRect.x = SCREEN_WIDTH / 2 - (quit_game_button.destRect.w / 2);
    quit_game_button.destRect.y = SCREEN_HEIGHT / 2 - (quit_game_button.destRect.h / 2) + 96;
    quit_game_button.originalRect = quit_game_button.destRect;

}

void UI::draw()
{
    SDL_RenderCopy(gRenderer, textures[0], NULL, &background);
    SDL_RenderCopy(gRenderer, start_game_button.texture, NULL, &start_game_button.destRect);
    SDL_RenderCopy(gRenderer, quit_game_button.texture, NULL, &quit_game_button.destRect);

}

bool UI::buttonIsHovered(SDL_Rect button, int x, int y)
{
    if (x >= button.x && x <= button.x + button.w &&
        y >= button.y && y <= button.y + button.h ) {
            return true;
        }
    return false;

}

void UI::handleMainMenuEvents(SDL_Event* e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    // left mouse button is clicked
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        // check which button is hovered
            // and mark correct button as clicked
        if(buttonIsHovered(start_game_button.destRect, x, y)) {
            buttonClick(&start_game_button);
        }
        if(buttonIsHovered(quit_game_button.destRect, x, y)) {
            buttonClick(&quit_game_button);
        }
    // left mouse button is released
        // button was clicked before
            // button that was clicked is STILL hovered
    } else if(e->type == SDL_MOUSEBUTTONUP) {
        if (start_game_button.isClicked) {
            if(buttonIsHovered(start_game_button.destRect, x, y)) {
                buttonRelease(&start_game_button);
                app.gameState = GAME;
            } else {
                buttonRelease(&start_game_button);
            }
        }

        if (quit_game_button.isClicked) {
            if(buttonIsHovered(quit_game_button.destRect, x, y)) {
                buttonRelease(&quit_game_button);
                app.quit = true;
            } else {
                buttonRelease(&quit_game_button);
            }
        }
    }
}

void UI::buttonClick(Button *button)
{
    button->isClicked = true;
    button->destRect.x = button->originalRect.x + 4;
    button->destRect.y = button->originalRect.y + 4;
    button->destRect.w = button->originalRect.w - 8;
    button->destRect.h = button->originalRect.h - 8;
}

void UI::buttonRelease(Button *button)
{
    button->isClicked = false;
    button->destRect = button->originalRect;
}

