#ifndef COINS_H
#define COINS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

class Coins : public Object {
	public:
		Coins();
		~Coins();
		void display(SDL_Renderer* gRenderer, SDL_Texture* background);
	private:
		int value;
};

#endif
