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
		bool loadFromFile(string path, SDL_Renderer* gRenderer);
		void free();
		void render(int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* renderer=NULL);
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

//extern SDL_Window* gWindow;
//extern SDL_Renderer* gRenderer;

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(string path, SDL_Renderer* gRenderer) {
	cout << "loadFromFile() accessed" << endl;  //hits this line, goes into free
	free();  //commented out gives Bus error (core dumped)
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) {
		cout << "Unable to load image " << path.c_str() << ". SDL_image Error: " << IMG_GetError() << endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL) {
			cout << "Unable to create texture from " << path.c_str() << ". SDL Error: " << SDL_GetError() << endl;
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
		cout << "free loaded surface" << endl;
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	cout << "free() accessed" << endl; //hits this
	if(mTexture != NULL) { //comment out this if statement and it still says double free, but it does access the lower lines
		cout << "free() if statement accessed" << endl; //doesn't get into if statement, this line displayed only once (not sure why/how that time was different)
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		//cout << "end of deleted if" << endl;
		
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}
