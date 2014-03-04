#pragma once
#include "../Utilities/Macros.h"
#include <SDL.h>
#include <stdio.h>


class Application {
public:
	bool quit;
	SDL_Event event;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* gXOut;

	Application();
	virtual ~Application();

	/*
	Creates an instance of Application
	*/
	static void createInstance();
	/*
	Returns an instance of Application
	*/
	static Application* getInstance();
	/*
	To be run on app close. Frees used memory.
	*/
	void onClose();

	/*
	Inits the instance, starts class objects.
	*/
	bool initInstance();
	/*
	Loads media needed by the application
	*/
	bool loadMedia();

	/*
	Main game loop.
	*/
	void runGame();
	
protected:
	static Application * mpsInstance;

};