#pragma once

#include <SDL.h>
#include <string>


class JN_SDLRenderer
{
public:
	JN_SDLRenderer();
	~JN_SDLRenderer();

	void Start();
	void End();

	void DrawLine(int, int, int, int, SDL_Color);
	void DrawTriangle(int, int, int, SDL_Color);
	void DrawReverseTriangle(int, int, int, SDL_Color);
	void DrawText(int, int, int, int, int, SDL_Color, std::string);

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
};