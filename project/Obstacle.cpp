#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Obstacle.h"
using namespace std;

// default constructor, also calls Object's constructor
Obstacle::Obstacle() : Object() {
	value = 5;
}

// is this necessary?
Obstacle::~Obstacle() {

}

// renders a red square to the game window
void Obstacle::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_Rect fillRect = {Object::getX(), Object::getY(), Object::getSize(), Object::getSize()};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

// score is sent in from main, decremented in this function, and then returned to main
int Obstacle::effect(int score) {
	score = score - value;
	return score;
}
