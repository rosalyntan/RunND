#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

class Object : public LTexture {
	public:
		Object();
		~Object();
		void setY(int);
		virtual void effect() = 0;
	private:
		int xPos;
		int yPos;
};

#endif
