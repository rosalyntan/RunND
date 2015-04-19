#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

// Key press surfaces constants
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

//Animation
const int BACKGROUND_ANIMATION_FRAMES = 4;
const int CHARACTER_ANIMATION_FRAMES = 4;
SDL_Rect gBackClips[BACKGROUND_ANIMATION_FRAMES];
SDL_Rect gCharClips[CHARACTER_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;
LTexture gCharacterTexture;

SDL_Renderer* gRenderer = NULL;

int main(int argc, char* argv[]) {
	//Start up SDL and create window
	if(!init()) {
		cout << "Failed to initialize." << endl;
	}
	else {
		//Load media
		if(!loadMedia()) {
			cout << "Failed to load media." << endl;
		}
		else {
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;

			int frame = 0;

			//Set default current surface
			//gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			//While application is running
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e)) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					//User presses a key
/*					else if(e.type == SDL_KEYDOWN) {
						//Select surfaces based on key press
						switch(e.key.keysym.sym) {
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;
							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;
							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;
							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;
							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
						}
					}*/
					else {
						SDL_Rect* currentClipBack = &gBackClips[frame / 4];
						SDL_Rect* currentClipChar = &gCharClips[frame / 4];
						gSpriteSheetTexture.render((SCREEN_WIDTH - currentClipBack->w)/2, (SCREEN_HEIGHT - currentClipBack->h)/2, currentClipBack,gRenderer);
						gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, (SCREEN_HEIGHT - currentClipChar->h)/2, currentClipChar,gRenderer);

						//need 2 different sets of frames
						SDL_RenderPresent(gRenderer);//loadFrom
						++frame;
						if(frame/4 >= BACKGROUND_ANIMATION_FRAMES) {
							frame = 0;
						}
					}
				}
				/*//Apply the image
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				//Update the surface
				SDL_UpdateWindowSurface(gWindow);*/
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("SDL Image Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else {
			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)) {
				cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError() << endl;
			}
			else {
				// Get window surface
				//gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL) {
		cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
		success = false;
	}

	//Load background sprite sheet texture
	if(!gSpriteSheetTexture.loadFromFile("Background_default.bmp",gRenderer)) {
		cout << "Failed to load animation texture" << endl;
		success = false;
	}
	else {
		gBackClips[0].x = 200;
		gBackClips[0].y = 0;
		gBackClips[0].w = 400;
		gBackClips[0].h = 600;

		gBackClips[1].x = 200;
		gBackClips[1].y = 0;
		gBackClips[1].w = 400;
		gBackClips[1].h = 600;

		gBackClips[2].x = 200;
		gBackClips[2].y = 0;
		gBackClips[2].w = 400;
		gBackClips[2].h = 600;

		gBackClips[3].x = 200;
		gBackClips[3].y = 0;
		gBackClips[3].w = 400;
		gBackClips[3].h = 600;
	}

	//Load character sprite sheet texture
	if(!gCharacterTexture.loadFromFile("Character_Sprite.bmp",gRenderer)) {
		cout << "Failed to load animation texture" << endl;
		success = false;
	}
	else {
		gCharClips[0].x = 0;
		gCharClips[0].y = 0;
		gCharClips[0].w = 80;
		gCharClips[0].h = 150;

		gCharClips[1].x = 150;
		gCharClips[1].y = 0;
		gCharClips[1].w = 80;
		gCharClips[1].h = 150;

		gCharClips[2].x = 300;
		gCharClips[2].y = 0;
		gCharClips[2].w = 80;
		gCharClips[2].h = 150;

		gCharClips[3].x = 450;
		gCharClips[3].y = 0;
		gCharClips[3].w = 80;
		gCharClips[3].h = 150;
	}
/*
	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("Background_default.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		cout << "Failed to load default image." << endl;
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("hello.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		cout << "Failed to load up image." << endl;
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("Background_default.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		cout << "Failed to load down image." << endl;
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("hello.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		cout << "Failed to load left image." << endl;
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("Background_default.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		cout << "Failed to load right image." << endl;
		success = false;
	}*/
	return success;
}

void close() {
/*	//Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;*/

	gSpriteSheetTexture.free(); //
	gCharacterTexture.free(); //

	SDL_DestroyRenderer(gRenderer); //
	gRenderer=NULL; //

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit(); //
	SDL_Quit();
}
/*
SDL_Surface* loadSurface(string path) {
	// The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) {
		cout << "Unable to load image " << path.c_str() << ". SDL_img Error: " << IMG_GetError() << endl;
	}
	else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if(optimizedSurface == NULL) {
			cout << "Unable to optimize image " << path.c_str() << ". SDL Error: " << SDL_GetError() << endl;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}*/
