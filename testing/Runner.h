#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

class Runner : public LTexture {
	public:
		Runner();
		~Runner();
		void jump();
//		void duck();
	private:
		int speed;
};

#endif
