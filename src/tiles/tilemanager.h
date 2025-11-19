#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TileManager {
  private:
    std::vector<std::string> tiles;
    std::vector<SDL_Texture *> textures;
    std::vector<std::vector<int>> map;

  public:
    TileManager();

    void loadMap(std::string path);
    void loadSprites();
    void drawTiles();
};

#endif
