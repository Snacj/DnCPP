#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TextureLoader {
  private:
    SDL_Texture *loadTexture(std::string path);

  public:
    TextureLoader();

    std::vector<SDL_Texture *> loadMedia(std::vector<std::string>);
};

#endif
