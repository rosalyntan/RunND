#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
using namespace std;

class Coin : public Object {
	public:
		Coin();
		~Coin();
		void display(SDL_Renderer* gRenderer, SDL_Texture* background);
		int effect(int);
	private:
		int value;
};

#endif
