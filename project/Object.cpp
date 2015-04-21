#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
//#include "LTexture.h"
using namespace std;

Object::Object() {
	xPos = 190;
	setY(300);
	setSize(20);
}

//Object::~Object() {

//}

void Object::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect fillRect = {190, yPos, size, size};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
	SDL_SetRenderTarget(gRenderer, NULL);
	SDL_RenderPresent(gRenderer);
}

void Object::setY(int y) {
	yPos = y;
}

void Object::setSize(int s) {
	size = s;
}
