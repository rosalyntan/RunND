#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
using namespace std;

class Background : public LTexture {
	public:
		Background();
		~Background();
	private:
		int direction; // switch case for various background sets
};

#endif
