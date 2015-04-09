#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

//LazyFoo Tutorial 10

//Texture wrapper class
class LTexture {
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(string path);
		void free();
		void render(int x, int y, SDL_Rect* clip = NULL);
		int getWidth();
		int getHEight();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

#endif
