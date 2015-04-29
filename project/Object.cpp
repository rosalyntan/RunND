#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

// default constructor
Object::Object(int w, int h) {
	setW(w);
	setH(h);
	setX(200-width/2);
	setY(300);
	setScale(15);
	frame = 0;
}

// is this necessary?
Object::~Object() {

}

// set y position of object
void Object::setY(int y) {
	yPos = y;
}

// set x position of object
void Object::setX(int x) {
	xPos = x;
}

// set width of object
void Object::setW(int s) {
	width = s;
}

void Object::setH(int s) {
	height = s;
}

void Object::setScale(int s) {
	scale = s;
}

// get functions
int Object::getX() {
	return xPos;
}

int Object::getY() {
	return yPos;
}

int Object::getW() {
	return width;
}

int Object::getH() {
	return height;
}

int Object::getScale() {
	return scale;
}

// increments frames
// every four frames the object moves down the path and also becomes a little larger to simulate perspective
void Object::nextFrame() {
	frame++;
	if (frame%4 == 0) {
		setScale(scale*1.25);
		setX(200-width/2);
		setY(yPos+scale*2);
	}
	if  (frame>=16) {
		setScale(15);
		setX(200-width/2);
		setY(300);
		frame = 0;	
	}
}

// get function
int Object::getFrame() {
	return frame;
}
