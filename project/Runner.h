#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Runner {
	public:
		Runner();
		~Runner();
		void jump();
	private:
		int speed;
};

#endif
