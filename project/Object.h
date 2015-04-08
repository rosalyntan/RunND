#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Object {
	public:
		Object();
		~Object();
		void setY(int);
		virtual void effect() = 0;
	private:
		int xPos = 400;
		int yPos;
};

#endif
