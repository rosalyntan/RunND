#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "LTexture.h"
using namespace std;

class Object {
	public:
		Object();
		~Object();
		void display(SDL_Renderer* gRenderer/*, SDL_Texture* background*/);
		void setY(int);
		void setX(int);
		void setSize(int);
		int getY();
		void nextFrame();	// sets up position and scale of the next frame for the flex point
	//	virtual void effect() = 0;
	private:
		int xPos;
		int yPos;
		int size;
};

#endif
