#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <string>
#include <vector>

#include "player.h"
#include "../main/application.h"
#include "../utils/textureLoader.h"
#include "../utils/globals.h"

Player::Player()
{
}

void Player::setup()
{
    animationTimer = 0;
    currentAnimationFrame = 1;

    direction = DOWN;
    speed = 3;
    texture = textures[10];

    // Camera
    screenX = SCREEN_WIDTH / 2 - (TILE_SIZE / 2);
    screenY = SCREEN_HEIGHT / 2 - (TILE_SIZE / 2);

    // Spawnpoint
    worldX = 20 * TILE_SIZE;
    worldY = 20 * TILE_SIZE;

    rect.x = screenX;
    rect.y = screenY;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    solidArea.w = 24;
    solidArea.h = 28;
    solidArea.x = 12;
    solidArea.y = 20;

    debugSolidArea = { screenX+solidArea.x, screenY+solidArea.y,
    solidArea.w, solidArea.h};

}

void Player::loadSprites()
{

    std::vector<std::string> sprites;

    sprites.push_back("player_up_1");
    sprites.push_back("player_up_2");
    sprites.push_back("player_down_1");
    sprites.push_back("player_down_2");
    sprites.push_back("player_left_1");
    sprites.push_back("player_left_2");
    sprites.push_back("player_right_1");
    sprites.push_back("player_right_2");
    sprites.push_back("player_up_idle_1");
    sprites.push_back("player_up_idle_2");
    sprites.push_back("player_down_idle_1");
    sprites.push_back("player_down_idle_2");
    sprites.push_back("player_left_idle_1");
    sprites.push_back("player_left_idle_2");
    sprites.push_back("player_right_idle_1");
    sprites.push_back("player_right_idle_2");

    textures = tl.loadMedia(sprites);

}

void Player::update()
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Handles animation
    animationTimer++;
    if (animationTimer >= 15) {
        animationTimer = 0;
        currentAnimationFrame = (currentAnimationFrame + 1) % 2;
    }

    collisionOn = false;

    float dx = 0;
    float dy = 0;

    // TODO Fix this later to allow diagonal Movement:
    // currently it breaks the collisionCheker
    // TODO replace else if with if statement

    // Handle Keyboard input
    if (keystates[SDL_SCANCODE_W]) {
        direction = UP;
        dy -= 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[0];
        } else {
            texture = textures[1];
        }
    }
    else if (keystates[SDL_SCANCODE_S]) {
        direction = DOWN;
        dy += 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[2];
        } else {
            texture = textures[3];
        }
    }
    else if (keystates[SDL_SCANCODE_A]) {
        direction = LEFT;
        dx -= 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[4];
        } else {
            texture = textures[5];
        }
    }
    else if (keystates[SDL_SCANCODE_D]) {
        direction = RIGHT;
        dx += 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[6];
        } else {
            texture = textures[7];
        }
    }

    if (!keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_S] &&
        !keystates[SDL_SCANCODE_A] && !keystates[SDL_SCANCODE_D]) {
        idle = true;
        if (direction == UP) {
            if (currentAnimationFrame == 0) {
                texture = textures[8];
            } else {
                texture = textures[9];
            }
        } else if (direction == DOWN) {
            if (currentAnimationFrame == 0) {
                texture = textures[10];
            } else {
                texture = textures[11];
            }
        } else if (direction == LEFT) {
            if (currentAnimationFrame == 0) {
                texture = textures[12];
            } else {
                texture = textures[13];
            }
        } else if (direction == RIGHT) {
            if (currentAnimationFrame == 0) {
                texture = textures[14];
            } else {
                texture = textures[15];
            }
        }
    } else {
        idle = false;
    }
    if (keystates[SDL_SCANCODE_O]) {
        debug = !debug;
    }

    // Normalize diagonal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    if (keystates[SDL_SCANCODE_LSHIFT])
        speed = 6;
    else
        speed = 3;

    app.getCollisionChecker().checkTileCollision(this);

    if (!collisionOn) {
        // printf("SpeedX: %f, SpeedY: %f\n", dx*speed, dy*speed);
        worldX += dx * speed;
        worldY += dy * speed;
    }
}

void Player::draw()
{
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);
    // debug
    if (debug) {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xAA);
        SDL_RenderFillRect(gRenderer, &debugSolidArea);
    }
}
