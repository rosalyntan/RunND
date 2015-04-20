#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

class Obstacle : public Object {
	public:
		Obstacle(int = 300);
		~Obstacle();
		void effect();
	private:
		int type;
		int isEffect;
};

#endif
