#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
 // The window we'll be rendering to
 SDL_Window* window = NULL;

 // The surface contained by the window
 SDL_Surface* screenSurface = NULL;

 // Initialize SDL
 if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
	cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
 }
 else {
	// Create Window
	window = SDL_CreateWindow("Animated Window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if ( window == NULL ) {
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
	}
	//else {
		// get window surface
		screenSurface = SDL_GetWindowSurface( window );
		SDL_Event windowEvent;
		int quit = 0;
		while(!quit) {
			// fill the surface with hex# color (sky blue)
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface -> format, 0x87, 0xce, 0xeb));
		
			// update the surface
			SDL_UpdateWindowSurface( window );
			
			// close if x-ed out
			if(SDL_PollEvent(&windowEvent)) {
				if(windowEvent.type == SDL_QUIT)
					quit=1;
			}
		}
		
	//}
	// Destroy window
	SDL_DestroyWindow( window );
	
	// Quit SDL subsystems
	SDL_Quit();
	
 }
 // Destroy window
 SDL_DestroyWindow( window );

 // Quit SDL subsystems
 SDL_Quit();
 
 return 0;
}
