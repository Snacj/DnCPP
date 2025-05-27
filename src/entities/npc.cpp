#include <SDL2/SDL.h>
#include <cctype>

#include "npc.h"
#include "../utils/textureLoader.h"
#include "../utils/globals.h"

Npc::Npc()
{

}

void Npc::setup()
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
    worldX = 25 * TILE_SIZE;
    worldY = 25 * TILE_SIZE;

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

void Npc::loadSprites()
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

void Npc::update()
{
    animationTimer++;
    if (animationTimer >= 15) {
        animationTimer = 0;
        currentAnimationFrame = (currentAnimationFrame + 1) % 2;
    }

    collisionOn = false;

    float dx = 0;
    float dy = 0;

    // TODO: implement basic AI

}
