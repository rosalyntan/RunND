#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Obstacle.h"
using namespace std;

// default constructor, also calls Object's constructor
Obstacle::Obstacle(SDL_Renderer* gRenderer, SDL_Window* gWindow) : Object() {
	loadMedia(gRenderer, gWindow);
	value = 2;
}

// is this necessary?
Obstacle::~Obstacle() {
	squirrel.free();
}

bool Obstacle::loadMedia(SDL_Renderer* gRenderer, SDL_Window* gWindow) {
	//Loading success flag
	bool success = true;

	//Load obstacle texture
	if(!squirrel.loadFromFile("squirrel.jpg", gRenderer)) {
		cout << "Failed to load obstacle texture" << endl;
		success = false;
	}
	else {
		current.x = 0;
		current.y = 0;
		current.w = Object::getSize();
		current.h = Object::getSize();
	}
	return success;
}

// renders a red square to the game window
void Obstacle::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	squirrel.render(Object::getX(), Object::getY(), &current, gRenderer);
/*	SDL_SetRenderTarget(gRenderer, background);
	SDL_Rect fillRect = {Object::getX(), Object::getY(), Object::getSize(), Object::getSize()};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);*/
}

// score is sent in from main, decremented in this function, and then returned to main
int Obstacle::effect(int score) {
	score = score - value;
	return score;
}
