#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect destRect;
    SDL_Rect originalRect;
    bool isHovered;
    bool isClicked;
} Button;

class UI {
  private:
    void createButtons();
    bool buttonIsHovered(SDL_Rect buttonRect, int x, int y);
    void buttonClick(Button *button);
    void buttonRelease(Button *button);

    std::vector<std::string> paths;
    std::vector<SDL_Texture *> textures;
    SDL_Rect background;

  public:
    UI();

    void loadSprites();
    void handleMainMenuEvents(SDL_Event *e);
    void createUIElements();
    void draw();
};

#endif
