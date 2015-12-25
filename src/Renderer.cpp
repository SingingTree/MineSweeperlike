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

void Renderer::render(Board &board)
{
	SDL_RenderClear(internal_renderer);
	render_board(internal_renderer, board);
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

std::tuple<int, int> Renderer::get_sprite_dimensions(Board &board)
{
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	return std::tuple<int, int>(w / board.get_width(), h / board.get_height());
}

void Renderer::render_board(SDL_Renderer *renderer, Board &board)
{
	SDL_Rect clipping_rect;
	int sprite_screen_width = std::get<0>(get_sprite_dimensions(board));
	int sprite_screen_height = std::get<1>(get_sprite_dimensions(board));
	for(int row = 0; row < board.get_height(); ++row)
	{
		for(int col = 0; col < board.get_width(); ++col)
		{
			int adjacency = std::get<1>(board.get_tile(row, col));
			clipping_rect.x = SPRITE_TEX_WIDTH * std::get<1>(number_sprite_row_col[adjacency]);
			clipping_rect.y = SPRITE_TEX_HEIGHT * std::get<0>(number_sprite_row_col[adjacency]);
			clipping_rect.w = SPRITE_TEX_WIDTH;
			clipping_rect.h = SPRITE_TEX_HEIGHT;
			render_sprite(
				internal_renderer,
				tile_sprite_sheet,
				&clipping_rect,
				sprite_screen_width * col,
				sprite_screen_height * row,
				board);
		}
	}
}

void Renderer::render_sprite (
	SDL_Renderer *renderer,
	SDL_Texture *sprite_sheet,
	SDL_Rect *clipping_rect,
	int x,
	int y,
	Board &board)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	std::tuple<int, int> destination_dimensions = get_sprite_dimensions(board);
	destination.w = std::get<0>(destination_dimensions);
	destination.h = std::get<1>(destination_dimensions);
	SDL_RenderCopy(renderer, sprite_sheet, clipping_rect, &destination);
}
