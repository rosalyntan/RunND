#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
using namespace std;

int main(int argc, char* argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if(window == NULL) {
		cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	SDL_Event windowEvent;
	while(true) {
		if(SDL_PollEvent(&windowEvent)) {
			if(windowEvent.type == SDL_QUIT)
				break;
		}
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	
	return 0;
}
