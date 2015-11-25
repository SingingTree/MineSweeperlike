#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : window(NULL)
{
}

int Renderer::init()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	internal_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(internal_renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window_surface = SDL_GetWindowSurface(window);
	if(window_surface == NULL)
	{
		std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	tile_sprite_sheet = IMG_Load("TileSpriteSheet.png");
	if(tile_sprite_sheet == NULL)
	{
		std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	return 0;
}

void Renderer::render()
{
	SDL_RenderClear(internal_renderer);
	SDL_RenderPresent(internal_renderer);
}

void Renderer::quit()
{
	if(tile_sprite_sheet != NULL)
	{
		SDL_FreeSurface(tile_sprite_sheet);
		tile_sprite_sheet = NULL;
	}
	if(internal_renderer != NULL)
	{
		SDL_DestroyRenderer(internal_renderer);
		internal_renderer = NULL;
	}
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	SDL_Quit();
}

SDL_Renderer * Renderer::get_internal_renderer()
{
	return internal_renderer;
}
