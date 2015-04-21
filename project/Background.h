#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "LTexture.h"
using namespace std;

class Background : public LTexture {
	public:
		Background();
		~Background();
		void turn(); //function replaces switch case that randomly generates turns
		SDL_Rect* frames(); //determines what frames are shown depending on the results of turn() function
		bool userTurn();
		int getNumTurn();
	private:
		int random; //random number generated for turn
		int difficulty; //used with random number generator, can be decreased to make game harder
		int frameBack;
		int dirTurn;
		int numTurn;
		int prev;
		SDL_Rect* currentClipBack;
		bool quit;
};

#endif
