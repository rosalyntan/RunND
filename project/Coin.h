// Inherited class from Object, class for coins along the path

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
		void display(SDL_Renderer* gRenderer, SDL_Texture* background); // renders coins to the window
		int effect(int); // increments the score when called
	private:
		int value; // how many points a coin gives when hit
};

#endif
