#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "Background.h"
using namespace std;

Background::Background():LTexture() {
	difficulty = 50;
	frameBack = 0;
	dirTurn = 0;
	prev = 0;
}


Background::~Background() {

}


void Background::turn() {
	random = rand() % difficulty; 

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


SDL_Rect* Background::frames() {
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

	return currentClipBack;
}


bool Background::userTurn() {
	if ((numTurn == 14) && (dirTurn == 2) && (userTurn==0))
		quit = true;	
	else if ((numTurn == 15) && (userTurn != dirTurn))
		quit = true;

	if (numTurn < 10)
	userTurn = 0;

	return quit;
}


int getNumTurn() {
	return numTurn;
}
