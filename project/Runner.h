// Class for the running character

#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

class Runner {
	public:
		Runner();
		~Runner();
		bool loadMedia(SDL_Renderer*, SDL_Window*);
		void frames();		// iterates through runner animation
		int display(int, int, SDL_Renderer*, int);
	private:
	 	int frameChar;		// current frame # of character, from 0-15
		int jump;		// jump variable
		SDL_Rect gCharClips[4];
		SDL_Rect* currentClipChar;	// section of image being render
		LTexture gCharacterTexture;	// character sprite sheet
};

#endif
