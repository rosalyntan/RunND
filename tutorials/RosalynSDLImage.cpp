#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The image we'll load and show on the screen
SDL_Surface* gHelloWorld = NULL;

int main(int argc, char* argv[]) {
	//Start up SDL and create window
	if(!init()) {
		cout << "Failed to initialize." << endl;
	}
	else {
		//Load media
		if(!loadMedia()) {
			cout << "Failed to load media." << endl;
		}
		else {
			//Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			//Update the surface
			SDL_UpdateWindowSurface(gWindow);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("SDL Image Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else {
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("hello.bmp");
	if(gHelloWorld == NULL) {
		cout << "Unable to load image. SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	return success;
}

void close() {
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
