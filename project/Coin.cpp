#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Coin.h"
using namespace std;

Coin::Coin() : Object() {
	value = 2;	
}

Coin::~Coin() {

}

void Coin::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_Rect fillRect = {Object::getX(), Object::getY(), Object::getSize(), Object::getSize()};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

int Coin::effect(int score) {
	score = score + value;
	return score;
}
