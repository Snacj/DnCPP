#include <SDL2/SDL.h>
#include <random>

#include "../main/application.h"
#include "../utils/globals.h"
#include "../utils/textureLoader.h"
#include "entity.h"
#include "npc.h"
#include "player.h"

Npc::Npc() { name = "NPC"; }

void Npc::setup() {
    animationTimer = 0;
    currentAnimationFrame = 1;

    walkingDirectionTimer = 0;

    direction = DOWN;
    speed = 1;
    texture = textures[10];

    // Spawnpoint
    worldX = 22 * TILE_SIZE;
    worldY = 22 * TILE_SIZE;

    rect.x = worldX;
    rect.y = worldY;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    solidArea.w = 24;
    solidArea.h = 28;
    solidArea.x = 12;
    solidArea.y = 20;

    debug = false;
    debugSolidArea = {worldX + solidArea.x, worldY + solidArea.y, solidArea.w,
                      solidArea.h};
}

void Npc::loadSprites() {

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

int Npc::randomNumber(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(start, end);

    int randomNum = distr(gen);

    return randomNum;
}

void Npc::update() {
    animationTimer++;
    if (animationTimer >= 15) {
        animationTimer = 0;
        currentAnimationFrame = (currentAnimationFrame + 1) % 2;
    }

    collisionOn = false;
    idle = false;

    float dx = 0;
    float dy = 0;

    // basic walking "AI"
    walkingDirectionTimer++;
    if (walkingDirectionTimer >= 50) {
        walkingDirectionTimer = 0;
        walkingDirection = randomNumber(0, 15);
        direction = randomNumber(0, 7);
    }

    if (walkingDirection <= 7) {
        if (direction == UP_LEFT) {
            dx -= 1;
            dy -= 1;
            if (currentAnimationFrame == 0) {
                texture = textures[4];
            } else {
                texture = textures[5];
            }
        } else if (direction == UP_RIGHT) {
            dx += 1;
            dy -= 1;
            if (currentAnimationFrame == 0) {
                texture = textures[6];
            } else {
                texture = textures[7];
            }
        } else if (direction == DOWN_LEFT) {
            dx -= 1;
            dy += 1;
            if (currentAnimationFrame == 0) {
                texture = textures[4];
            } else {
                texture = textures[5];
            }
        } else if (direction == DOWN_RIGHT) {
            dx += 1;
            dy += 1;
            if (currentAnimationFrame == 0) {
                texture = textures[6];
            } else {
                texture = textures[7];
            }
        } else if (direction == UP) {
            dy -= 1;
            if (currentAnimationFrame == 0) {
                texture = textures[0];
            } else {
                texture = textures[1];
            }
        } else if (direction == DOWN) {
            dy += 1;
            if (currentAnimationFrame == 0) {
                texture = textures[2];
            } else {
                texture = textures[3];
            }
        } else if (direction == LEFT) {
            dx -= 1;
            if (currentAnimationFrame == 0) {
                texture = textures[4];
            } else {
                texture = textures[5];
            }
        } else if (direction == RIGHT) {
            dx += 1;
            if (currentAnimationFrame == 0) {
                texture = textures[6];
            } else {
                texture = textures[7];
            }
        }
    } else {
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
    }

    // Normalize diagnoal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    app.getCollisionChecker().checkTileCollision(this);

    if (!collisionOn) {
        worldX += dx * speed;
        worldY += dy * speed;

        screenX = worldX - app.getPlayer().worldX + app.getPlayer().screenX;
        screenY = worldY - app.getPlayer().worldY + app.getPlayer().screenY;

        rect.x = screenX;
        rect.y = screenY;

        debugSolidArea.x = screenX + solidArea.x;
        debugSolidArea.y = screenY + solidArea.y;
    }
}
