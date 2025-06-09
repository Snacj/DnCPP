#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#include "globals.h"
#include "textureLoader.h"

TextureLoader::TextureLoader() {

}

std::vector<SDL_Texture*> TextureLoader::loadMedia(std::vector<std::string> paths)
{
    std::string spritePath = "assets/sprites/";
    std::string fileFormat = ".png";
    std::vector<SDL_Texture*> textures;


    SDL_Texture* texture;

	// Load PNG texture
    for ( std::string path: paths ) {
        std::string fullPath = spritePath + path + fileFormat;
        texture = loadTexture(fullPath);
        if( texture == NULL )
        {
            printf( "Failed to load texture image!\n" );
        }
        textures.push_back(texture);
    }

    // Load font
    // https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php

	return textures;
}

SDL_Texture* TextureLoader::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
