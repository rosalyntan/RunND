#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LTexture.h"
using namespace std;

class Background {
	public:
		Background();
		~Background();
		void turn(int, int); //function replaces switch case that randomly generates turns
		void frames(); //determines what frames are shown depending on the results of turn() function
		bool lose(int);
		int getNumTurn();
		bool loadMedia(SDL_Renderer*, SDL_Window*, /*LTexture*,*/ TTF_Font*);
		void display(int, int, SDL_Renderer*);
		int getFrameBack();
		SDL_Texture* getText();
		TTF_Font* gFont; //
		void resetNumTurn();
	private:
		int frameBack;
		int dirTurn;
		int numTurn;
		int prev;
		SDL_Rect* currentClipBack;
		SDL_Rect gBackClips[13];
		LTexture gSpriteSheetTexture;
		LTexture gTextTexture;
};

#endif
