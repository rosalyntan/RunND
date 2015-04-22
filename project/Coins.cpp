#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Coins.h"
using namespace std;

Coins::Coins() : Object() {
	value = 10;	
}

Coins::~Coins() {

}

void Coins::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_Rect fillRect = {Object::getX(), Object::getY(), Object::getSize(), Object::getSize()};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
}
