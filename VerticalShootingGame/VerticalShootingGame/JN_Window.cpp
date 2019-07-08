#include "JN_Window.h"

#include <iostream>

JN_Window::JN_Window()
{
	window = SDL_CreateWindow("Vertical Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 250, 250, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Window failed to be created\n";
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
}


JN_Window::~JN_Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}