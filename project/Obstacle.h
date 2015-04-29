// Inherited class from Object, class for obstacles along the path

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
#include "LTexture.h"
using namespace std;

class Obstacle : public Object {
	public:
		Obstacle(SDL_Renderer* gRenderer, SDL_Window* gWindow);
		~Obstacle();
		bool loadMedia(SDL_Renderer* gRenderer, SDL_Window* gWindow);
		void display(SDL_Renderer* gRenderer, SDL_Texture* background); // renders obstacle to window
		int effect(int); // decrements the score
	private:
		int value; // amount the score is decremented by when the character hits an obstacle
		SDL_Rect current;
		LTexture squirrel;
};

#endif
