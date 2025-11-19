#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>

#include "../utils/globals.h"
#include "entity.h"

class Npc : public Entity {
  private:
    int randomNumber(int start, int end);
    int walkingDirection;
    // entity stats, texts etc.

  public:
    Npc();

    void loadSprites() override;
    void setup() override;
    void update() override;
};

#endif
