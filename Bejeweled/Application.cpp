#include "Application.h"
#include "windows.h"
#include <string.h>
#include <assert.h>


Application* Application::mpsInstance = NULL;

Application::Application() {
	gWindow = NULL;
	gScreenSurface = NULL;
	gXOut = NULL;
	quit = false;
}

void Application::createInstance() {
	assert(mpsInstance == NULL);

	mpsInstance = myNew Application();
}

Application* Application::getInstance() {
	assert(mpsInstance != NULL);
	return mpsInstance;
}

bool Application::initInstance() {
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("Beerjeweled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	//Load needed media
	success = loadMedia();
	return success;
}

bool Application::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP("../assets/x.bmp");
	if (gXOut == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "../assets/x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void Application::runGame() {
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&event) != 0) {
			//User requests quit
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		//Apply the image
		SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
}

void Application::onClose() {
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Application::~Application() {
	mpsInstance = NULL;
}
