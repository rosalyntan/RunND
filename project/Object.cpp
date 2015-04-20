#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

Object::Object():LTexture() {
	setY(300);
}

Object::~Object() {

}

void Object::setY(int y) {
	yPos = y;
}
