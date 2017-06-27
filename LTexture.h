#pragma once
#include <string>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

/* Texture wrapper used to make different functions easier
using the SDL_Texture class*/


class LTexture
{
private:
	// The hardware texture holding the spritesheet
	SDL_Texture* mTexture;

	// The constraints of the image and/or sprite
	int mWidth;
	int mHeight;

public:
	LTexture();
	~LTexture();

	// Used to load the spritesheet from the specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	// Free the memory of the texture
	void free();

	// Render the image to the specified location
	// Clip refers to the specific box on the texture
	void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL);

	// Returns the width and height of the sheet respectively
	int getWidth();
	int getHeight();
};

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
LTexture::~LTexture()
{
	free();
}


// Load the texture from 'path' and pass in the global Renderers
bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	SDL_Texture* newTexture = NULL;

	// Load the image as an SDL_Surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Loaded surface could not be initialized for %s.\n", path.c_str());
	}
	else
	{
		// Set colorKey
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create a texture from the SDL Surface
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from surface for %s.\n", path.c_str());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Remove the now unused surface
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	mWidth = 0;
	mHeight = 0;
}

void LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip)
{
	// Render the image, pass in dimensions as an SDL_Rect
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// If we are using a sprite sheet, we may need a specific piece of the image
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}