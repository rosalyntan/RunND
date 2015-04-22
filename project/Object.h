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
		virtual void display(SDL_Renderer* gRenderer, SDL_Texture* background) = 0;
		void setY(int);
		void setX(int);
		void setSize(int);
		int getX();
		int getY();
		int getSize();
		void nextFrame(); // sets up position and scale of the next frame for the flex point
		int getFrame();
	//	virtual void effect() = 0;
	private:
		int xPos;
		int yPos;
		int size;
		int frame;
};

#endif
