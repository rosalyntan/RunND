#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
//#include "LTexture.h"
using namespace std;

Object::Object() {
	xPos = 100;
	setY(300);
}

//Object::~Object() {

//}

void Object::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect fillRect1 = {190, 300, 20, 20};
	SDL_Rect fillRect2 = {190, 350, 20, 20};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect1);
	SDL_RenderFillRect(gRenderer, &fillRect2);
	SDL_SetRenderTarget(gRenderer, NULL);
	SDL_RenderPresent(gRenderer);
}

void Object::setY(int y) {
	yPos = y;
}
