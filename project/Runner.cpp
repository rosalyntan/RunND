#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Runner.h"
using namespace std;

Runner::Runner(){
	frameChar = 0;
	jump = 0;
}

Runner::~Runner() {
	gCharacterTexture.free(); 
}

bool Runner::loadMedia(SDL_Renderer* gRenderer, SDL_Window* gWindow) {
	//Loading success flag
	bool success = true;

	//Load character sprite sheet texture
	if(!gCharacterTexture.loadFromFile("Character_Sprite.png", gRenderer)) {
		cout << "Failed to load animation texture" << endl;
		success = false;
	}
	else {
		gCharClips[0].x = 0;
		gCharClips[0].y = 0;
		gCharClips[0].w = 80;
		gCharClips[0].h = 150;

		gCharClips[1].x = 150;
		gCharClips[1].y = 0;
		gCharClips[1].w = 80;
		gCharClips[1].h = 150;

		gCharClips[2].x = 300;
		gCharClips[2].y = 0;
		gCharClips[2].w = 80;
		gCharClips[2].h = 150;

		gCharClips[3].x = 450;
		gCharClips[3].y = 0;
		gCharClips[3].w = 80;
		gCharClips[3].h = 150;
	}
	return success;
}

void Runner::frames() {	
	++frameChar;		// increment frameChar
	if(frameChar/4 >= 4) {
		frameChar = 0;	// loop back to first frame 
	}
}

//originally a void function, returns direction now because direction needs to update in main also
int Runner::display(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer, int direction) {
	currentClipChar = &gCharClips[frameChar / 4];	// assign current frame based on frameChar (each sprite stays up for 4 frames to get good animation tempo)
	if (direction == 1) {	// if jumping					
		gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 12*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);	// render sprite in jumping location
		jump++;
		if (jump > 4) {		// jumps for 4 frame
			direction = 0;
			jump = 0;
		}
	}
	else
		gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 14*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);	// render sprite in running location
	return direction;
}

