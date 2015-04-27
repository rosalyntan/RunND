#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "Background.h"
//#include "LTexture.h"
using namespace std;

Background::Background() {
//	difficulty = 50;
	frameBack = 0;
	dirTurn = 0;
	prev = 0;
	numTurn = 0;
//	LTexture gSpriteSheetTexture;
//	BACKGROUND_ANIMATION_FRAMES = 13;
}


Background::~Background() {
	gSpriteSheetTexture.free(); 
}


void Background::turn(int random) {
	//random = rand() % difficulty; 

	switch(random) {
		case 1: //both turns
			frameBack = 1;
			dirTurn = 2;
			prev = random;
			break;
		case 2: //turn left
			frameBack = 16;
			dirTurn = 3;
			prev = random;	
			break;
		case 3: //turn right
			frameBack = 32;
			dirTurn = 4;
			prev = random;
			break;
		default: //straight
			dirTurn = 1;
			prev = random;
			break;
	}
}


void Background::frames() {
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
	else if (dirTurn == 1) { //straight
		currentClipBack = &gBackClips[frameBack];
		numTurn = 0;
		dirTurn = 0;
	}
}


bool Background::lose(int userTurn) {
	if ((numTurn == 14) && (dirTurn == 2) && (userTurn==0))
		quit = true;	
	else if ((numTurn == 15) && (userTurn != dirTurn))
		quit = true;

//	if (numTurn < 10)
//	userTurn = 0;

	return quit;
}

int Background::getNumTurn() {
	return numTurn;
}

bool Background::loadMedia(SDL_Renderer* gRenderer, SDL_Window* gWindow) {
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
	return success;
}

void Background::display(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer) {
	gSpriteSheetTexture.render((SCREEN_WIDTH - currentClipBack->w)/2, (SCREEN_HEIGHT - currentClipBack->h)/2, currentClipBack, gRenderer);
}

int Background::getFrameBack() {
	return frameBack;
}
