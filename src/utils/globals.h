#ifndef GLOBALS_H
#define GLOBALS_H

#include "textureLoader.h"
#include <SDL2/SDL.h>

#define ORIGINAL_TILE_SIZE 16 // 16x16 px
#define SCALE 3
#define TILE_SIZE ORIGINAL_TILE_SIZE * SCALE

#define SCREEN_COLS 16
#define SCREEN_ROWS 12

#define MAX_WORLD_COL 100
#define MAX_WORLD_ROW 100

#define SCREEN_WIDTH SCREEN_COLS * TILE_SIZE
#define SCREEN_HEIGHT SCREEN_ROWS * TILE_SIZE

class Application;
extern Application app;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TextureLoader tl;

#endif

