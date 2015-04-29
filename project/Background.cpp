#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sstream> //int to string
#include "Background.h"
#include "LTexture.h"
using namespace std;

Background::Background() {
	frameBack = 0;
	dirTurn = 1;
	prev = 0;
	numTurn = 0;
	scoreFont = NULL; 
	pauseFont = NULL;
	startFont = NULL;
}

Background::~Background() {
	gSpriteSheetTexture.free(); 
	LogoTexture.free();
	LevelTexture.free();
	ScoreTextTexture.free();
	StartTextTexture.free();
	PauseTextTexture.free();
	TTF_CloseFont( scoreFont ); 
	scoreFont = NULL; 
	TTF_CloseFont( pauseFont ); 
	pauseFont = NULL; 
	TTF_CloseFont( startFont ); 
	startFont = NULL; 
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

bool Background::loadBackground(SDL_Renderer* gRenderer, SDL_Window* gWindow) {
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
	return success;
}

void Background::loadLogo(SDL_Renderer* gRenderer) {
	if(!LogoTexture.loadFromFile("RUN_ND.png", gRenderer))
		cout << "Failed to load animation texture" << endl;
}

void Background::loadLevel(SDL_Renderer* gRenderer) {

	//Load level sprite sheet
	if(!LevelTexture.loadFromFile("EndGame_sprite.png", gRenderer)) {
		cout << "Failed to load animation texture" << endl;
	}
	else {
		//Stepan - Level 1
		LevelClips[0].x = 0;
		LevelClips[0].y = 0;
		LevelClips[0].w = 400;
		LevelClips[0].h = 600;

		LevelClips[1].x = 400;
		LevelClips[1].y = 0;
		LevelClips[1].w = 400;
		LevelClips[1].h = 600;

		LevelClips[2].x = 800;
		LevelClips[2].y = 0;
		LevelClips[2].w = 400;
		LevelClips[2].h = 600;

		LevelClips[3].x = 1200;
		LevelClips[3].y = 0;
		LevelClips[3].w = 400;
		LevelClips[3].h = 600;

		//Library - Level 2
		LevelClips[4].x = 0;
		LevelClips[4].y = 600;
		LevelClips[4].w = 400;
		LevelClips[4].h = 600;

		LevelClips[5].x = 400;
		LevelClips[5].y = 600;
		LevelClips[5].w = 400;
		LevelClips[5].h = 600;

		LevelClips[6].x = 800;
		LevelClips[6].y = 600;
		LevelClips[6].w = 400;
		LevelClips[6].h = 600;

		LevelClips[7].x = 1200;
		LevelClips[7].y = 600;
		LevelClips[7].w = 400;
		LevelClips[7].h = 600;

		//Grotto - Level 3
		LevelClips[8].x = 0;
		LevelClips[8].y = 1200;
		LevelClips[8].w = 400;
		LevelClips[8].h = 600;

		LevelClips[9].x = 400;
		LevelClips[9].y = 1200;
		LevelClips[9].w = 400;
		LevelClips[9].h = 600;

		LevelClips[10].x = 800;
		LevelClips[10].y = 1200;
		LevelClips[10].w = 400;
		LevelClips[10].h = 600;

		LevelClips[11].x = 1200;
		LevelClips[11].y = 1200;
		LevelClips[11].w = 400;
		LevelClips[11].h = 600;

		//Dome (1-3) - Level 4
		LevelClips[12].x = 1600;
		LevelClips[12].y = 0;
		LevelClips[12].w = 400;
		LevelClips[12].h = 600;

		LevelClips[13].x = 1600;
		LevelClips[13].y = 600;
		LevelClips[13].w = 400;
		LevelClips[13].h = 600;

		LevelClips[14].x = 1600;
		LevelClips[14].y = 1200;
		LevelClips[14].w = 400;
		LevelClips[14].h = 600;
	}
}

void Background::loadFont(SDL_Renderer* gRenderer, int score) {
	
	//change printf to cout
	//Initialize Font
	if(TTF_Init() == -1) { 
		printf("SDL_ttf could not initialize. SDL_ttf Error: %s\n", TTF_GetError()); 
	}
	else {

		//Set pause font and text
		if (pauseFont == NULL)
			pauseFont = TTF_OpenFont("Aparajita.ttf", 60); 
		if(pauseFont == NULL) { 
			printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError()); 
		} 
		SDL_Color pauseColor = {158, 131, 70}; 
		PauseTextTexture.loadFromRenderedText("PAUSE", pauseColor, gRenderer, pauseFont); 

		//Display start
		if(startFont == NULL)
			startFont = TTF_OpenFont("Aparajita.ttf", 40); 
		if(startFont == NULL) { 
			printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError()); 
		} 
		SDL_Color startColor = {158, 131, 70}; 
		StartTextTexture.loadFromRenderedText("Click to Start", startColor, gRenderer, startFont);

		//Display score 
		if(scoreFont == NULL)
			scoreFont = TTF_OpenFont("Aparajita.ttf", 40); 
		if(scoreFont == NULL) { 
			printf("Failed to load font. SDL_ttf Error: %s\n", TTF_GetError()); 
		} 
		SDL_Color scoreColor = {16, 46, 106}; 
		string scoreString = static_cast<ostringstream*>( &(ostringstream() << score) ) ->str();
		ScoreTextTexture.loadFromRenderedText("Score: " + scoreString, scoreColor, gRenderer, scoreFont); 
	} 
}

void Background::display(int SCREEN_WIDTH, int SCREEN_HEIGHT, int score, SDL_Renderer* gRenderer) { //render texture frame to window
	gSpriteSheetTexture.render((SCREEN_WIDTH - currentClipBack->w)/2, (SCREEN_HEIGHT - currentClipBack->h)/2, currentClipBack, gRenderer); 
	ScoreTextTexture.render(255, 0, 0, gRenderer);
}

void Background::displayStart(SDL_Renderer* gRenderer) {
	LogoTexture.render(50, 225, 0, gRenderer);
	StartTextTexture.render(115, 350, 0, gRenderer);
}

void Background::displayLevel(int SCREEN_WIDTH, int SCREEN_HEIGHT, int frame, SDL_Renderer* gRenderer) { //render texture frame to window
	currentClipLevel = &LevelClips[frame];
	LevelTexture.render((SCREEN_WIDTH - currentClipLevel->w)/2, (SCREEN_HEIGHT - currentClipLevel->h)/2, currentClipLevel, gRenderer); 
}

void Background::displayPause(SDL_Renderer* gRenderer) {
	PauseTextTexture.render(125, 275, 0, gRenderer);
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
