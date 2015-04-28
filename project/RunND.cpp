#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "LTexture.h"
#include "Object.h"
#include "Coin.h"
#include "Obstacle.h"
#include "Background.h"
#include "Runner.h"
using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

//Initialize window and renderer
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* scoreFont;
TTF_Font* pauseFont;
LTexture* gTextTexture;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Background * back = new Background;  //Initialize call to background class
	Runner * character = new Runner;
	int score;

	//Start up SDL and create window
	if(!init()) {
		cout << "Failed to initialize." << endl;
	}
	else {
		//Load media
		if(!loadMedia() || !(back -> loadMedia(gRenderer, gWindow, scoreFont, pauseFont)) || !(character -> loadMedia(gRenderer, gWindow))) {
			cout << "Failed to load media." << endl;
		}
		else {
			//Main loop flag
			bool quit = false;

			SDL_Event e; //Event handler
			int direction = 0;
			int random = 0;
			int userTurn = 0;
			int difficulty = 50; //used with random number generator, can be decreased to make game harder
			bool start = false;
			int pause = 0;

			//While application is running
			while(true) {
				int beginning = 0;
				start = false;
				score = 10;
				while(!start) {
					SDL_SetRenderTarget(gRenderer, back -> getText());
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_Rect startScreen = {0, 0, 400, 600};
					SDL_RenderFillRect(gRenderer, &startScreen);
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x88, 0xFF, 0xFF);
					SDL_Rect startButton = {100, 200, 200, 200};
					SDL_RenderFillRect(gRenderer, &startButton);
					SDL_SetRenderTarget(gRenderer, NULL);
					SDL_RenderPresent(gRenderer);
					if(SDL_PollEvent(&e)) {
						int x = e.button.x;
						int y = e.button.y;
						if (e.button.button == SDL_BUTTON_LEFT && x>100 && x<300 && y>200 && y<400) {
							start = true;
						}
					}
					if(e.type == SDL_QUIT) {
						return 0;
					}
				}
				quit = false;
				Coin* coinA = new Coin;
				Coin* coinB = new Coin;
				Obstacle* obstacleA = new Obstacle;
				bool visibleCoinA = false;
				bool visibleCoinB = false;
				bool visibleObstacleA = false;
				back -> resetNumTurn();
				while(!quit) {
					if (beginning < 50) {beginning++;}
					if (SDL_PollEvent(&e)) {
						if(e.type == SDL_KEYDOWN) {
							switch(e.key.keysym.sym) { //switch case for key press
								case SDLK_UP: //jump
									direction = 1;
									break;
								case SDLK_LEFT: //turn left
									userTurn = 3;
									break;
								case SDLK_RIGHT: //turn right
									userTurn = 4;
									break;
								case SDLK_SPACE: //pause
									pause = 2;	// has to be two because in while loop automatically enters the if statements the first time 
							}
						}
						//User requests quit
						else if(e.type == SDL_QUIT) {
							return 0;
						}
					}
					
					// pause game when space bar is pressed
					while (pause) {
						// create pause icon (a rectangle that says pause)
						SDL_SetRenderDrawColor(gRenderer, 0x00, 0x88, 0xFF, 0xFF);
						SDL_Rect pauseIcon = {100, 250, 200, 100};
						SDL_RenderFillRect(gRenderer, &pauseIcon);
						SDL_SetRenderTarget(gRenderer, NULL);
						SDL_RenderPresent(gRenderer);
						if (SDL_PollEvent(&e)) {
							if (e.type == SDL_QUIT) { return 0;}
							if (e.key.keysym.sym == SDLK_SPACE) {
								pause--;
							}
						}
					}
					
					//calls to background function to display appropriate frames
					if (back -> getNumTurn() == 0) {
						random = rand() % difficulty;
						back -> turn(random, beginning);
					}
					back -> frames();
					quit = (back -> lose(userTurn));
					if (back -> getNumTurn()<10)
						userTurn = 0;
					back -> display(400, 600, gRenderer);

					//call coinA
					if ((random < 5) && (back -> getFrameBack())%16==0 && !visibleCoinA) {
						//Object * coin = new Object;
						visibleCoinA = true;
					}
					if (visibleCoinA) {
						coinA -> nextFrame();
						// add another variable canIncrement
						if(coinA -> getFrame() >= 12 && direction != 1) {
							if(coinA -> getFrame() == 12)
								score = coinA -> effect(score); // get it to only increment once 
							else if (coinA -> getFrame() >= 15) {
								//delete a;
								visibleCoinA = false;
							}
						}
						if (visibleCoinA) {
							coinA -> display(gRenderer, (back -> getText()));
						}
					}
					//call coinB
					if ((random > 45) && (back -> getFrameBack())%16==0 && !visibleCoinB) {
						//Object * coin = new Object;
						visibleCoinB = true;
					}
					if (visibleCoinB) {
						coinB -> nextFrame();
						if(coinB -> getFrame() >= 12 && direction != 1) {
							if(coinB -> getFrame() == 12)
								score = coinB -> effect(score);
							else if (coinB -> getFrame() >= 15) {
								//delete a;
								visibleCoinB = false;
							}
						}
						if (visibleCoinB) {
							coinB -> display(gRenderer, (back -> getText()));
						}
					}
					//call obstacleA
					if((random > 20 && random <= 25) && (back -> getFrameBack())%16 == 0 && !visibleObstacleA) {
						visibleObstacleA = true;
					}
					if(visibleObstacleA) {
						obstacleA -> nextFrame();
						if(obstacleA -> getFrame() >= 12 && direction != 1) {
							if(obstacleA -> getFrame() == 12)
								score = obstacleA -> effect(score);
							if(obstacleA -> getFrame() >= 15) {
								visibleObstacleA = false;
							}
						}
						if(visibleObstacleA) {
							obstacleA -> display(gRenderer, (back -> getText()));
						}
					}

					character -> frames();
					direction = character -> display(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer, direction);

					SDL_RenderPresent(gRenderer);
				}
				cout << score << endl; // delete later
			}
		}
	}
	//Free resources and close SDL
	delete back;
	delete character;
	close();

	return 0;
} //end of main

bool init() { //Initialize SDL window
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("Run ND", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else {
			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)) {
				cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError() << endl;
			}
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Initialize Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
	if(gRenderer == NULL) {
		cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
		success = false;
	}

	return success;
}

void close() {
	
	SDL_DestroyRenderer(gRenderer); 
	gRenderer=NULL; 

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit(); 
	SDL_Quit();
	TTF_Quit();
}
