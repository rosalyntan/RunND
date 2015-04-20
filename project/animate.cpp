#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//Initialize window and renderer
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Animation
const int BACKGROUND_ANIMATION_FRAMES = 13;
const int CHARACTER_ANIMATION_FRAMES = 4;
SDL_Rect gBackClips[BACKGROUND_ANIMATION_FRAMES];
SDL_Rect gBackClipsS[1];
SDL_Rect gBackClipsB[4];
SDL_Rect gCharClips[CHARACTER_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;
LTexture gCharacterTexture;

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
			int frameBack = 0;
		 	int frameChar = 0;
			int direction = 0;
			int jump = 0;
			int numTurn = 0;
			int dirTurn = 0;
			SDL_Rect* currentClipBack;
		
			//While application is running
			while(!quit) { 
				if (SDL_PollEvent(&e)) {
					if(e.type == SDL_KEYDOWN) {
						switch(e.key.keysym.sym) {
							case SDLK_UP: //jump
								direction = 1;
								break;
							case SDLK_DOWN: //both turns
								frameBack = 1;
								dirTurn = 2;
								break;
							case SDLK_LEFT: //turn left
								frameBack = 16;
								dirTurn = 3;
								break;
							case SDLK_RIGHT: //turn right
								frameBack = 32;
								dirTurn = 4;
								break;
						}
					}
					//User requests quit
					else if(e.type == SDL_QUIT) {
						quit = true;
					}
				}

				if (dirTurn == 2) { //both turns
					if (numTurn < 16) {
						currentClipBack = &gBackClips[frameBack/4 + 1];
						++numTurn;
						dirTurn = 2;
						++frameBack;
					}
					if(frameBack >= 16) {
						frameBack = 0;
						numTurn = 0;
						dirTurn=0;
					}
				}
				else if (dirTurn == 3) { //left turn
					if (numTurn < 16) {
						currentClipBack = &gBackClips[frameBack/4 + 1];
						++numTurn;
						dirTurn = 3;
						++frameBack;
					}
					if(frameBack >= 32) {
						frameBack = 0;
						numTurn = 0;
						dirTurn=0;
					}
				}
				else if (dirTurn == 4) { //right turn
					if (numTurn < 16) {
						currentClipBack = &gBackClips[frameBack/4 + 1];
						++numTurn;
						dirTurn = 4;
						++frameBack;
					}
					if(frameBack >= 48) {
						frameBack = 0;
						numTurn = 0;
						dirTurn=0;
					}
				}
				else {
					currentClipBack = &gBackClips[frameBack];
					numTurn = 0;
					dirTurn = 0;
			/*		++frameBack;
					if(frameBack >= 1) {
						frameBack = 0;
					}*/
				}


				SDL_Rect* currentClipChar = &gCharClips[frameChar / CHARACTER_ANIMATION_FRAMES];
				gSpriteSheetTexture.render((SCREEN_WIDTH - currentClipBack->w)/2, (SCREEN_HEIGHT - currentClipBack->h)/2, currentClipBack, gRenderer);
				//sprite jumps when up arrow is pressed
				if (direction == 1) {						
					gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 12*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);
					jump++;
					if (jump > 4) {
						direction = 0;
						jump = 0;
					}
				}
				else
					gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 14*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);

				SDL_RenderPresent(gRenderer);

				//continuously cycle through all frames for character sprite
				++frameChar;
				if(frameChar/CHARACTER_ANIMATION_FRAMES >= CHARACTER_ANIMATION_FRAMES) {
					frameChar = 0;
				}
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
	if(!gSpriteSheetTexture.loadFromFile("Background_sprite.bmp", gRenderer)) {
		cout << "Failed to load animation texture" << endl;
		success = false;
	}
	else {
		//straight
		gBackClips[0].x = 0;
		gBackClips[0].y = 0;
		gBackClips[0].w = 400;
		gBackClips[0].h = 600;

		//both turns
		gBackClips[1].x = 400;
		gBackClips[1].y = 0;
		gBackClips[1].w = 400;
		gBackClips[1].h = 600;

		gBackClips[2].x = 800;
		gBackClips[2].y = 0;
		gBackClips[2].w = 400;
		gBackClips[2].h = 600;

		gBackClips[3].x = 1200;
		gBackClips[3].y = 0;
		gBackClips[3].w = 400;
		gBackClips[3].h = 600;

		gBackClips[4].x = 1600;
		gBackClips[4].y = 0;
		gBackClips[4].w = 400;
		gBackClips[4].h = 600;

		//left turn
		gBackClips[5].x = 400;
		gBackClips[5].y = 600;
		gBackClips[5].w = 400;
		gBackClips[5].h = 600;

		gBackClips[6].x = 800;
		gBackClips[6].y = 600;
		gBackClips[6].w = 400;
		gBackClips[6].h = 600;

		gBackClips[7].x = 1200;
		gBackClips[7].y = 600;
		gBackClips[7].w = 400;
		gBackClips[7].h = 600;

		gBackClips[8].x = 1600;
		gBackClips[8].y = 600;
		gBackClips[8].w = 400;
		gBackClips[8].h = 600;

		//left turn
		gBackClips[9].x = 400;
		gBackClips[9].y = 1200;
		gBackClips[9].w = 400;
		gBackClips[9].h = 600;

		gBackClips[10].x = 800;
		gBackClips[10].y = 1200;
		gBackClips[10].w = 400;
		gBackClips[10].h = 600;

		gBackClips[11].x = 1200;
		gBackClips[11].y = 1200;
		gBackClips[11].w = 400;
		gBackClips[11].h = 600;

		gBackClips[12].x = 1600;
		gBackClips[12].y = 1200;
		gBackClips[12].w = 400;
		gBackClips[12].h = 600;
	}

	//Load character sprite sheet texture
	if(!gCharacterTexture.loadFromFile("Character_Sprite.png", gRenderer)) {
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
	return success;
}

void close() {
	gSpriteSheetTexture.free(); 
	gCharacterTexture.free(); 

	SDL_DestroyRenderer(gRenderer); 
	gRenderer=NULL; 

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit(); 
	SDL_Quit();
}

