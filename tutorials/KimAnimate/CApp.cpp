//Kim's 2.5D animation tutorial from http://www.sdltutorials.com/sdl-tutorial-basics
//Part 1 - Basics

#include <SDL2/SDL.h>
#include "CApp.h"

CApp::CApp() {
	Running = true;
}

int CApp::OnExecute() {
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while (Running) {
		while (SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();	
	}

	OnCleanup();

	return 0;
}

int main(int argc, char* argv[]) {
	CApp theApp;

	return theApp.OnExecute();
}
