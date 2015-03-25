//Kim's OpenGL tutorials
#include <SDL2/SDL.h>
#include <stdio.h>


bool init(); //create window
bool loadMedia();
void close(); //free media, close window


//window details, global variables
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* Image = NULL;


bool init() {
	bool success = true;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//initialize SDL window (main function from first tutorial) 
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow ("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created. %s\n", SDL_GetError());
			success = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	return success;
}


bool loadMedia() {
	bool success = true;

	Image = SDL_LoadBMP("hello.bmp");
	if (Image == NULL) {
		printf("Unable to load image");
		success = false;
	}

	return success;
}


void close() {
	SDL_FreeSurface(Image);
	Image = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}


int main (int argc, char* args[]) {
	
	if (!init()) {
		printf("Failed to initialize");
	}
	else {
		if (!loadMedia()) {
			printf("Failed to load media");
		}
		else {
			SDL_BlitSurface(Image, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	close();
	
	return 0;
}
