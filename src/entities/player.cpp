#include <SDL2/SDL.h>
#include <cstdio>
#include <string>
#include <vector>

#include "player.h"
#include "../main/application.h"
#include "../utils/textureLoader.h"
#include "../utils/globals.h"

Player::Player()
{
    name = "Player";
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

    texture_path.push_back("player_up_1");
    texture_path.push_back("player_up_2");
    texture_path.push_back("player_down_1");
    texture_path.push_back("player_down_2");
    texture_path.push_back("player_left_1");
    texture_path.push_back("player_left_2");
    texture_path.push_back("player_right_1");
    texture_path.push_back("player_right_2");
    texture_path.push_back("player_up_idle_1");
    texture_path.push_back("player_up_idle_2");
    texture_path.push_back("player_down_idle_1");
    texture_path.push_back("player_down_idle_2");
    texture_path.push_back("player_left_idle_1");
    texture_path.push_back("player_left_idle_2");
    texture_path.push_back("player_right_idle_1");
    texture_path.push_back("player_right_idle_2");

    textures = tl.loadMedia(texture_path);

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
    idle = false;

    float dx = 0;
    float dy = 0;

    // Handle Keyboard input
    if (keystates[SDL_SCANCODE_W] && keystates[SDL_SCANCODE_A]) {
        direction = UP_LEFT;
        dx -= 1.0f;
        dy -= 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[4];
        } else {
            texture = textures[5];
        }
    }
    else if (keystates[SDL_SCANCODE_W] && keystates[SDL_SCANCODE_D]) {
        direction = UP_RIGHT;
        dx += 1.0f;
        dy -= 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[6];
        } else {
            texture = textures[7];
        }
    }
    else if (keystates[SDL_SCANCODE_S] && keystates[SDL_SCANCODE_A]) {
        direction = DOWN_LEFT;
        dx -= 1.0f;
        dy += 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[4];
        } else {
            texture = textures[5];
        }
    }
    else if (keystates[SDL_SCANCODE_S] && keystates[SDL_SCANCODE_D]) {
        direction = DOWN_RIGHT;
        dx += 1.0f;
        dy += 1.0f;
        if (currentAnimationFrame == 0) {
            texture = textures[6];
        } else {
            texture = textures[7];
        }
    }
    else if (keystates[SDL_SCANCODE_W]) {
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
        } else if (direction == LEFT ||
                direction == UP_LEFT ||
                direction == DOWN_LEFT) {
            if (currentAnimationFrame == 0) {
                texture = textures[12];
            } else {
                texture = textures[13];
            }
        } else if (direction == RIGHT ||
                direction == UP_RIGHT ||
                direction == DOWN_RIGHT) {
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

    // sprinting
    if (keystates[SDL_SCANCODE_LSHIFT])
        speed = 6;
    else
        speed = 3;

    // Normalize diagonal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

//    printf("Current speedX: %f, Current speedY: %f\n", dx*speed, dy*speed);

    app.getCollisionChecker().checkTileCollision(this);

    if (!collisionOn) {
        // printf("SpeedX: %f, SpeedY: %f\n", dx*speed, dy*speed);
        worldX += dx * speed;
        worldY += dy * speed;
    }
}
