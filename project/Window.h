#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Window {
	public:
		Window();
		void left();
		void right();
	private:
		int level;
		int points;
		float time;
};

#endif
