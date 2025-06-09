#include <SDL2/SDL.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#include "collisionChecker.h"
#include "../utils/globals.h"

void CollisionChecker::checkTileCollision(Entity* entity)
{
    int entityLeftWorldX = entity->worldX + entity->solidArea.x;
    int entityRightWorldX = entity->worldX + entity->solidArea.x + entity->solidArea.w;
    int entityTopWorldY = entity->worldY + entity->solidArea.y;
    int entityBottomWorldY = entity->worldY + entity->solidArea.y + entity->solidArea.h;

    int entityLeftCol = entityLeftWorldX / TILE_SIZE;
    int entityRightCol = entityRightWorldX / TILE_SIZE;
    int entityTopRow = entityTopWorldY / TILE_SIZE;
    int entityBottomRow = entityBottomWorldY / TILE_SIZE;

    int tileNum1, tileNum2, tileNum3, tileNum4;

    switch (entity->direction) {
        case UP:
            entityTopRow = (entityTopWorldY - entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityTopRow];
            tileNum2 = collisionMap[entityRightCol][entityTopRow];
            if(tileNum1 == 1 || tileNum2 == 1) {
                entity->collisionOn = true;
            }
            break;
        case DOWN:
            entityBottomRow = (entityBottomWorldY + entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityBottomRow];
            tileNum2 = collisionMap[entityRightCol][entityBottomRow];
            if(tileNum1 == 1 || tileNum2 == 1) {
                entity->collisionOn = true;
            }
            break;
        case LEFT:
            entityLeftCol = (entityLeftWorldX - entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityTopRow];
            tileNum2 = collisionMap[entityLeftCol][entityBottomRow];
            if(tileNum1 == 1 || tileNum2 == 1) {
                entity->collisionOn = true;
            }
            break;
        case RIGHT:
            entityRightCol = (entityRightWorldX + entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityRightCol][entityTopRow];
            tileNum2 = collisionMap[entityRightCol][entityBottomRow];
            if(tileNum1 == 1 || tileNum2 == 1) {
                entity->collisionOn = true;
            }
            break;
        case UP_LEFT:
            entityTopRow = (entityTopWorldY - entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityTopRow];
            tileNum2 = collisionMap[entityRightCol][entityTopRow];

            entityLeftCol = (entityLeftWorldX - entity->speed) / TILE_SIZE;
            tileNum3 = collisionMap[entityLeftCol][entityTopRow];
            tileNum4 = collisionMap[entityLeftCol][entityBottomRow];

            if(tileNum1 == 1 || tileNum2 == 1 || tileNum3 == 1 || tileNum4 == 1) {
                entity->collisionOn = true;
            }
            break;
        case UP_RIGHT:
            entityTopRow = (entityTopWorldY - entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityTopRow];
            tileNum2 = collisionMap[entityRightCol][entityTopRow];

            entityRightCol = (entityRightWorldX + entity->speed) / TILE_SIZE;
            tileNum3 = collisionMap[entityRightCol][entityTopRow];
            tileNum4 = collisionMap[entityRightCol][entityBottomRow];

            if(tileNum1 == 1 || tileNum2 == 1 || tileNum3 == 1 || tileNum4 == 1) {
                entity->collisionOn = true;
            }
             break;
        case DOWN_LEFT:
            entityBottomRow = (entityBottomWorldY + entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityBottomRow];
            tileNum2 = collisionMap[entityRightCol][entityBottomRow];

            entityLeftCol = (entityLeftWorldX - entity->speed) / TILE_SIZE;
            tileNum3 = collisionMap[entityLeftCol][entityTopRow];
            tileNum4 = collisionMap[entityLeftCol][entityBottomRow];

            if(tileNum1 == 1 || tileNum2 == 1 || tileNum3 == 1 || tileNum4 == 1) {
                entity->collisionOn = true;
            }
             break;
        case DOWN_RIGHT:
            entityBottomRow = (entityBottomWorldY + entity->speed) / TILE_SIZE;
            tileNum1 = collisionMap[entityLeftCol][entityBottomRow];
            tileNum2 = collisionMap[entityRightCol][entityBottomRow];

            entityRightCol = (entityRightWorldX + entity->speed) / TILE_SIZE;
            tileNum3 = collisionMap[entityRightCol][entityTopRow];
            tileNum4 = collisionMap[entityRightCol][entityBottomRow];

            if(tileNum1 == 1 || tileNum2 == 1 || tileNum3 == 1 || tileNum4 == 1) {
                entity->collisionOn = true;
            }
             break;
        default:
            break;

    }
}

//bool CollisionChecker::checkObjectCollision(Entity entity1, Entity entity2)
//{
//}

void CollisionChecker::loadCollisionMap( std::string path )
{
    std::ifstream file(path);

    if (!file.is_open()) printf("Error opening Collisionmap file.");

    std::string line;
    while(std::getline(file,line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        std::stringstream ss(line);
        std::string value;

        while(std::getline(ss, value, ',')) {
            if(!value.empty()) {
                row.push_back(std::stoi(value));
            }
        }

        collisionMap.push_back(row);
    }

    file.close();

}

