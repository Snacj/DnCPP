#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "../entities/entity.h"

class CollisionChecker {
  private:
  public:
    void checkTileCollision(Entity *entity);
    bool checkObjectCollision(Entity entity1, Entity entity2);
    void loadCollisionMap(std::string path);

    std::vector<std::vector<int>> collisionMap;
};
