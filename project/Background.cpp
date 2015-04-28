#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Background.h"
#include "LTexture.h"
using namespace std;

Background::Background() {
	frameBack = 0;
	dirTurn = 1;
	prev = 0;
	numTurn = 0;
	gFont = NULL; 
}


Background::~Background() {
	gSpriteSheetTexture.free(); 
	TTF_CloseFont( gFont ); 
	gFont = NULL; 
}


void Background::turn(int random, int beginning) { //use random number generated to determine which set of turn frames should be displayed
	switch(random) {
		case 1: //both turns
			frameBack = 1;
			dirTurn = 2;
			prev = random;
			if (beginning < 50) {
				dirTurn = 1;
				prev = 4;
				frameBack = 0;
			}
			break;
		case 2: //turn left
			frameBack = 16;
			dirTurn = 3;
			prev = random;
			if (beginning < 50) {
				dirTurn = 1;
				prev = 4;
				frameBack = 0;
			}	
			break;
		case 3: //turn right
			frameBack = 32;
			dirTurn = 4;
			prev = random;
			if (beginning < 50) {
				dirTurn = 1;
				prev = 4;
				frameBack = 0;
			}
			break;
		default: //straight
			dirTurn = 1;
			prev = random;
			break;
	}
}


void Background::frames() { //display turn frames based on turn() function
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
			dirTurn=1;
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
			dirTurn=1;
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
			dirTurn=1;
		}
	}
	else if (dirTurn == 1) { //straight
		currentClipBack = &gBackClips[frameBack];
		numTurn = 0;
		dirTurn = 1;
	}
}


bool Background::lose(int userTurn) {
	bool quit2 = false;
	if ((numTurn == 14) && (dirTurn == 2) && (userTurn==0))
		quit2 = true;	
	else if ((numTurn == 15) && (userTurn != dirTurn))
		quit2 = true;

	if (quit2) {
		frameBack = 0;
		dirTurn = 1;
		prev = 0;
		numTurn = 0;
	}

	return quit2;
}

int Background::getNumTurn() {
	return numTurn;
}

bool Background::loadMedia(SDL_Renderer* gRenderer, SDL_Window* gWindow, TTF_Font* gFont) {
	//Loading success flag
	bool success = true;

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

	//Initialize Font
	if( TTF_Init() == -1 ) { 
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() ); 
		success = false; 
	}
	else {
		 //Open the font 
		gFont = TTF_OpenFont( "lazy.ttf", 28 ); 
		if( gFont == NULL ) { 
			printf( "Failed to load font. SDL_ttf Error: %s\n", TTF_GetError() ); 
			success = false; 
		} 
		else { //Display score
			SDL_Color textColor = { 100, 0, 0 }; 
			if( !ScoreTextTexture.loadFromRenderedText("Score:", textColor, gRenderer, gFont) ) { 
				printf( "Failed to render text texture!\n" );
				success = false; 
			} 
		}
	} 
	return success;
}

void Background::display(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer) { //render texture frame to window
	gSpriteSheetTexture.render((SCREEN_WIDTH - currentClipBack->w)/2, (SCREEN_HEIGHT - currentClipBack->h)/2, currentClipBack, gRenderer);
	ScoreTextTexture.render(250, 15, 0, gRenderer );
}

int Background::getFrameBack() {
	return frameBack;
}

SDL_Texture* Background::getText() {
	return gSpriteSheetTexture.getTexture();
}

void Background::resetNumTurn() {
	numTurn = 0;
}
