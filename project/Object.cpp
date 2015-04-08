#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

Object::Object() {
	new 
	setY(300);
}

Object::~Object() {

}

void Object::setY(int y) {
	yPos = y;
}
