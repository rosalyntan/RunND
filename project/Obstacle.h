#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

class Obstacle : public Object {
	public:
		Obstacle();
		~Obstacle();
		void display(SDL_Renderer* gRenderer, SDL_Texture* background);
		int effect(int);
	private:
		int value;
};

#endif
