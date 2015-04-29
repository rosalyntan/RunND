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
		if(!loadMedia() || !(back -> loadBackground(gRenderer, gWindow)) || !(character -> loadMedia(gRenderer, gWindow))) {
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
			int win = 0;
			int level = 1;
			int timelapse = 500;
			//back -> loadLevel(gRenderer);
			//While application is running
			while(true) {
				int beginning = 0;
				start = false;
				score = 0;
				while(!start) {
					if (back -> getNumTurn() == 0) {
						random = rand() % 10;
						back -> turn(random, beginning);
					}
					back -> frames();
					back -> display(400, 600, score, gRenderer);
					character -> frames();
					direction = character -> display(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer, direction);
					back -> loadLogo(gRenderer);
					back -> loadFont(gRenderer, score);

					// start button
					SDL_SetRenderDrawColor(gRenderer,0x9E, 0x83, 0x46, 0x00); // gold
					SDL_Rect startBack = {15, 190, 370, 220};
					SDL_RenderFillRect(gRenderer, &startBack);
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x10, 0x2E, 0x6A);
					SDL_Rect startButton = {25, 200, 350, 200};
					SDL_RenderFillRect(gRenderer, &startButton);
					back -> displayStart(gRenderer);
					SDL_SetRenderTarget(gRenderer, NULL);
					SDL_RenderPresent(gRenderer);
					if(SDL_PollEvent(&e)) {
						int x = e.button.x;
						int y = e.button.y;
						if (e.button.button == SDL_BUTTON_LEFT && x>15 && x<385 && y>190 && y<410) {
							start = true;
						}
					}
					if(e.type == SDL_QUIT) {
						return 0;
					}
				}
				direction = 0;
				quit = false;
				Coin* coinA = new Coin;
				Coin* coinB = new Coin;
				Obstacle* obstacleA = new Obstacle(gRenderer, gWindow);
				bool visibleCoinA = false;
				bool visibleCoinB = false;
				bool visibleObstacleA = false;
				back -> resetNumTurn();
				while(!quit) {
					back -> loadFont(gRenderer, score);
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
						SDL_SetRenderDrawColor(gRenderer, 0x9E, 0x83, 0x46, 0x00); //gold box
						SDL_Rect pauseBack = {90, 240, 220, 120};
						SDL_RenderFillRect(gRenderer, &pauseBack);
						SDL_SetRenderDrawColor(gRenderer, 0x00, 0x10, 0x2E, 0x6A);
						SDL_Rect pauseIcon = {100, 250, 200, 100};
						SDL_RenderFillRect(gRenderer, &pauseIcon);
						SDL_SetRenderTarget(gRenderer, NULL);
						back -> displayPause(gRenderer);
						SDL_RenderPresent(gRenderer);
						if (SDL_PollEvent(&e)) {
							if (e.type == SDL_QUIT) { return 0;}
							if (e.key.keysym.sym == SDLK_SPACE) {
								pause--;
							}
						}
					}
					
					// display beginning of level message
					while (timelapse) {
						SDL_SetRenderDrawColor(gRenderer,0x9E, 0x83, 0x46, 0x00); // gold
						SDL_Rect winBack = {15, 20, 370, 110};
						SDL_RenderFillRect(gRenderer, &winBack);
						SDL_SetRenderDrawColor(gRenderer, 0x00, 0x10, 0x2E, 0x6A);
						SDL_Rect winButton = {25, 30, 350, 90};
						SDL_RenderFillRect(gRenderer, &winButton);
						back -> displayLevelBegin(gRenderer, level);
						SDL_SetRenderTarget(gRenderer, NULL);
						SDL_RenderPresent(gRenderer);
						timelapse--;
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
					back -> display(400, 600, score, gRenderer);

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
						else if(coinA -> getFrame() >= 12 && direction == 1) {
							if(coinA -> getFrame() >= 15) {
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
						else if(coinB -> getFrame() >= 12 && direction == 1) {
							if(coinB -> getFrame() >= 15) {
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
							else if(obstacleA -> getFrame() >= 15) {
								visibleObstacleA = false;
							}
						}
						else if(obstacleA -> getFrame() >= 12 && direction == 1) {
							if(obstacleA -> getFrame() >= 15) {
								visibleObstacleA = false;
							}
						}
						if(visibleObstacleA) {
							obstacleA -> display(gRenderer, (back -> getText()));
						}
					}

					if (score < 0) //can't have a negative score
						quit = true;
					else if (score >= 10) //completes level after getting 100 points
						win = 1;

					character -> frames();
					direction = character -> display(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer, direction);

					SDL_RenderPresent(gRenderer);
					if(win) {	// end of each level
						back -> loadLevel(gRenderer);
						int currentFrame = level*4 - 4;
						for (int i = 1; i < 16; i++) {
							if (currentFrame<15) {
								back -> displayLevel(SCREEN_WIDTH, SCREEN_HEIGHT, currentFrame, gRenderer);
							}
							if (i % 4 == 0) { currentFrame++; }
							character -> frames();
							direction = character -> display(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer, direction);
							SDL_RenderPresent(gRenderer);
						}
						// end of level message
						timelapse = 0;
						while (timelapse < 500) {
							SDL_SetRenderDrawColor(gRenderer,0x9E, 0x83, 0x46, 0x00); // gold
							SDL_Rect winBack = {15, 20, 370, 110};
							SDL_RenderFillRect(gRenderer, &winBack);
							SDL_SetRenderDrawColor(gRenderer, 0x00, 0x10, 0x2E, 0x6A);
							SDL_Rect winButton = {25, 30, 350, 90};
							SDL_RenderFillRect(gRenderer, &winButton);
							back -> displayLevelEnd(gRenderer, level);
							SDL_SetRenderTarget(gRenderer, NULL);
							SDL_RenderPresent(gRenderer);
							timelapse++;
						}
						win = 0;
						score = 0;
						level++;
						beginning = 0;
					}
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
