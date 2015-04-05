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
	private:
		int location;
};

#endif
