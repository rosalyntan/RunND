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
	++frameChar;
	if(frameChar/4 >= 4) {
		frameChar = 0;
	}
}

//originally a void function, returns direction now because direction needs to update in main also
int Runner::display(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer, int direction) {
	currentClipChar = &gCharClips[frameChar / 4];
	if (direction == 1) {						
		gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 12*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);
		jump++;
		if (jump > 4) {
			direction = 0;
			jump = 0;
		}
	}
	else
		gCharacterTexture.render((SCREEN_WIDTH - currentClipChar->w)/2, 14*(SCREEN_HEIGHT - currentClipChar->h)/15, currentClipChar, gRenderer);
	return direction;
}

