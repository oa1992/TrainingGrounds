#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL);

	int getWidth();

	int getHeight();

private:
	// The hardware texture
	SDL_Texture* mTexture;

	// The image constraints
	int mWidth;
	int mHeight;
};

bool init();
bool loadMedia();
void setFenceLocation();
void setBackgroundLocation();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Screen constraints
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUMBER_OF_FENCES = 43;
SDL_Rect fencePos[NUMBER_OF_FENCES];
LTexture gFenceTexture;

const int NUMBER_OF_PLANTS = 5;
SDL_Rect plantPos[NUMBER_OF_PLANTS];
LTexture gPlantTexture;

// Fireballs
const int FIREBALL_ANIMATION_FRAMES = 2;
SDL_Rect gFireBallClips[FIREBALL_ANIMATION_FRAMES];
LTexture gFireBallTexture;


LTexture gGrassTexture;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	free();

	SDL_Texture* optimizedTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Loaded Surface could not be initialized for %s\n", path.c_str());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		optimizedTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (optimizedTexture == NULL)
		{
			printf("Texture could not be loaded from surface for %s\n", path.c_str());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = optimizedTexture;
	return mTexture != NULL;
	
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
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

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if (!gFenceTexture.loadFromFile("resources/fenceDitherWArm.png"))
	{
		printf("Failed to load fenecDitherWArm\n");
		success = false;
	}
	else
	{
		setFenceLocation();
	}
	
	if (!gGrassTexture.loadFromFile("resources/grassStartbg.png"))
	{
		printf("Failed to load grassStartbg.png");
		success = false;
	}

	if (!gPlantTexture.loadFromFile("resources/grassPlant.png"))
	{
		printf("Failed to loadd grassPlant.png");
		success = false;
	}

	if (!gFireBallTexture.loadFromFile("resources/fireBallAnimationTesting.png"))
	{
		printf("Failed to load fireBallAnimationTesting.png");
		success = false;
	}

	// temp set fireball clips
	gFireBallClips[0].x = 0;
	gFireBallClips[0].y = 0;
	gFireBallClips[0].w = 20;
	gFireBallClips[0].h = 26;

	gFireBallClips[1].x = 20;
	gFireBallClips[1].y = 0;
	gFireBallClips[1].w = 20;
	gFireBallClips[1].h = 26;

	return success;
}

void setFenceLocation()
{
	for(int i = 0; i < NUMBER_OF_FENCES; i++)
	{
		fencePos[i].x = i * gFenceTexture.getWidth();
		fencePos[i].y = SCREEN_HEIGHT - gFenceTexture.getHeight();
		fencePos[i].w = gFenceTexture.getWidth();
		fencePos[i].h = gFenceTexture.getHeight();
	}
}

void setBackgroundLocation()
{
	for (int i = 0; i < SCREEN_WIDTH; i += gGrassTexture.getWidth())
	{
		for (int j = 0; j < SCREEN_HEIGHT; j += gGrassTexture.getHeight())
		{
			gGrassTexture.render(i, j, NULL);

			if (i == 15 * gGrassTexture.getWidth() && j == 15 * gGrassTexture.getHeight())
			{
				gPlantTexture.render(i, j, NULL);
			}
		}
	}
}

void close()
{
	gFenceTexture.free();
	gGrassTexture.free();
	gPlantTexture.free();
	gFireBallTexture.free();

	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!init())
	{
		printf("Failed to initialize\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			// Current animation frame
			int fireBallFrame = 0;
			int waiting = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				setBackgroundLocation();

				// Render current frame of fireball
				SDL_Rect* currentClip = &gFireBallClips[fireBallFrame/FIREBALL_ANIMATION_FRAMES];
				gFireBallTexture.render(50, 50, currentClip);

				// Render fences
				for (int i = 0; i < NUMBER_OF_FENCES; i++)
				{
					gFenceTexture.render(fencePos[i].x, fencePos[i].y, NULL);
				}
				

				//Update screen
				SDL_RenderPresent(gRenderer);
				++waiting;
				if (waiting / 100 >= 1)
				{
					waiting = 0;
					++fireBallFrame;
					if (fireBallFrame / FIREBALL_ANIMATION_FRAMES >= FIREBALL_ANIMATION_FRAMES)
					{
						fireBallFrame = 0;

					}
				}
			}
		}
	}
	close();
	return 0;
}