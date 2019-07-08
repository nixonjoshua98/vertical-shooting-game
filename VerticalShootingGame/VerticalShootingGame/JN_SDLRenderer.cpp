#include "JN_SDLRenderer.h"

#include <iostream>
#include <SDL_ttf.h>


JN_SDLRenderer::JN_SDLRenderer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0)
	{
		std::cout << "This did not go as expected\n";
		exit(1);
	}

	window = SDL_CreateWindow("Vertical Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 250, 250, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Window failed to be created\n";
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
}


JN_SDLRenderer::~JN_SDLRenderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
}


void JN_SDLRenderer::Start()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);
}


void JN_SDLRenderer::End()
{
	SDL_RenderPresent(renderer);
}


void JN_SDLRenderer::DrawLine(int x1, int y1, int x2, int y2, SDL_Color col)
{
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);

	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


void JN_SDLRenderer::DrawTriangle(int x, int y, int size, SDL_Color col)
{
	int top_x = x, top_y = y - (size);
	int left_x = x - (size / 2), left_y = y;
	int right_x = x + (size / 2), right_y = y;

	DrawLine(top_x, top_y, left_x, left_y, col);
	DrawLine(top_x, top_y, right_x, right_y, col);
	DrawLine(left_x, left_y, right_x, right_y, col);
}


void JN_SDLRenderer::DrawReverseTriangle(int x, int y, int size, SDL_Color col)
{
	int btm_x = x, btm_y = y + size;
	int left_x = x - (size / 2), left_y = y;
	int right_x = x + (size / 2), right_y = y;

	DrawLine(btm_x, btm_y, left_x, left_y, col);
	DrawLine(btm_x, btm_y, right_x, right_y, col);
	DrawLine(left_x, left_y, right_x, right_y, col);
}


void JN_SDLRenderer::DrawText(int x, int y, int w, int h, int size, SDL_Color col, std::string txt)
{
	TTF_Font* font = TTF_OpenFont("Assets/Acme-Regular.ttf", size);

	SDL_Surface* surface = TTF_RenderText_Solid(font, txt.c_str(), col);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect{ x - (w / 2), y - (h / 2), w, h };

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);	
}
