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
		bool loadBackground(SDL_Renderer*, SDL_Window*);
		void loadLogo(SDL_Renderer*);
		void loadLevel(SDL_Renderer*); //
		void loadFont(SDL_Renderer*, int);
		void display(int, int, int, SDL_Renderer*);
		void displayLevel(int, int, int, SDL_Renderer*);
		void displayStart(SDL_Renderer*);
		void displayPause(SDL_Renderer*); 
		void displayLevelEnd(SDL_Renderer*, int); 
		void displayLevelBegin(SDL_Renderer*, int); 
		int getFrameBack();
		void resetNumTurn();
		SDL_Texture* getText();
		TTF_Font* scoreFont; 
		TTF_Font* startFont; 
		TTF_Font* pauseFont;
		TTF_Font* levelFont;
	private:
		int frameBack;
		int dirTurn;
		int numTurn;
		int prev;
		SDL_Rect* currentClipBack;
		SDL_Rect* currentClipLevel;	//
		SDL_Rect gBackClips[13];
		SDL_Rect LevelClips[15];	//
		LTexture gSpriteSheetTexture;
		LTexture LogoTexture;
		LTexture LevelTexture;		//
		LTexture ScoreTextTexture;
		LTexture StartTextTexture;
		LTexture PauseTextTexture;
		LTexture Level1EndTextTexture;
		LTexture Level2EndTextTexture;
		LTexture Level3EndTextTexture;
		LTexture Level4EndTextTexture;
		LTexture Level1BeginTextTexture_1;
		LTexture Level2BeginTextTexture_1;
		LTexture Level3BeginTextTexture_1;
		LTexture Level4BeginTextTexture_1;
		LTexture Level1BeginTextTexture_2;
		LTexture Level2BeginTextTexture_2;
		LTexture Level3BeginTextTexture_2;
		LTexture Level4BeginTextTexture_2;
};

#endif
