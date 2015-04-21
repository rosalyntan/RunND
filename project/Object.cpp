#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
//#include "LTexture.h"
using namespace std;

Object::Object() {
	setSize(15);
	setX(200-size/2);
	setY(300);
}

Object::~Object() {

}

void Object::display(SDL_Renderer* gRenderer, SDL_Texture* background) {
	SDL_SetRenderTarget(gRenderer, background);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect fillRect = {xPos, yPos, size, size};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
	// Testing location: DELETE LATER
	setSize(size*1.5);
	setX(200-size/2);
	setY(yPos+size*2);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect fillRect1 = {xPos, yPos, size, size};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect1);
	SDL_SetRenderTarget(gRenderer, NULL);
	setSize(size*1.5);
	setX(200-size/2);
	setY(yPos+size*2);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect fillRect2 = {xPos, yPos, size, size};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect2);
	SDL_SetRenderTarget(gRenderer, NULL);
	//SDL_RenderPresent(gRenderer);
}

void Object::setY(int y) {
	yPos = y;
}

void Object::setX(int x) {
	xPos = x;
}

void Object::setSize(int s) {
	size = s;
}
