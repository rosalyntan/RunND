#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

// default constructor
Object::Object() {
	setSize(15);
	setX(200-size/2);
	setY(300);
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

// set size of object
void Object::setSize(int s) {
	size = s;
}

// get functions
int Object::getX() {
	return xPos;
}

int Object::getY() {
	return yPos;
}

int Object::getSize() {
	return size;
}

// increments frames
// every four frames the object moves down the path and also becomes a little larger to simulate perspective
void Object::nextFrame() {
	frame++;
	if (frame%4 == 0) {
		setSize(size*1.25);
		setX(200-size/2);
		setY(yPos+size*2);
	}
	if  (frame>=16) {
		setSize(15);
		setX(200-size/2);
		setY(300);
		frame = 0;	
	}
}

// get function
int Object::getFrame() {
	return frame;
}
