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

	SDL_Surface *tile_sprite_surface = IMG_Load("TileSpriteSheet.png");
	if(tile_sprite_surface == NULL)
	{
		std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	tile_sprite_sheet = SDL_CreateTextureFromSurface(internal_renderer, tile_sprite_surface);
	if(tile_sprite_sheet == NULL) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(tile_sprite_surface);
		return 1;
	}

	SDL_FreeSurface(tile_sprite_surface);
	

	return 0;
}

void Renderer::render()
{
	SDL_Rect clipping_rect;
	clipping_rect.x = 0;
	clipping_rect.y = 0;
	clipping_rect.h = 256;
	clipping_rect.w = 256;
	SDL_RenderClear(internal_renderer);
	render_sprite(internal_renderer, tile_sprite_sheet, &clipping_rect, 0, 0);
	SDL_RenderPresent(internal_renderer);
}

void Renderer::quit()
{
	if(tile_sprite_sheet != NULL)
	{
		SDL_DestroyTexture(tile_sprite_sheet);
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

void Renderer::render_sprite (
	SDL_Renderer *renderer,
	SDL_Texture *sprite_sheet,
	SDL_Rect *clipping_rect,
	int x,
	int y)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.w = clipping_rect->w;
	destination.h = clipping_rect->h;
	SDL_RenderCopy(renderer, sprite_sheet, clipping_rect, &destination);
}
