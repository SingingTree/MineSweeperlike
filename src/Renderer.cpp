#include "Renderer.h"
#include "Board.h"
#include <iostream>

//#define RENDERER_DEBUG_SHOW_ALL

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

	SDL_Surface *play_again_surface = IMG_Load("PlayAgain.png");
	if(play_again_surface == NULL)
	{
		std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	play_again_tex = SDL_CreateTextureFromSurface(internal_renderer, play_again_surface);
	if(play_again_tex == NULL) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(play_again_surface);
		return 1;
	}

	SDL_FreeSurface(play_again_surface);

	SDL_Surface *yeah_surface = IMG_Load("Yeah.png");
	if(play_again_surface == NULL)
	{
		std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	yeah_tex = SDL_CreateTextureFromSurface(internal_renderer, yeah_surface);
	if(play_again_tex == NULL) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(play_again_surface);
		return 1;
	}

	SDL_FreeSurface(yeah_surface);

	SDL_Surface *nah_surface = IMG_Load("Nah.png");
	if(play_again_surface == NULL)
	{
		std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	nah_tex = SDL_CreateTextureFromSurface(internal_renderer, nah_surface);
	if(play_again_tex == NULL) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(play_again_surface);
		return 1;
	}

	SDL_FreeSurface(nah_surface);
	

	return 0;
}

void Renderer::render_in_game(Board &board)
{
	SDL_RenderClear(internal_renderer);
	render_board(board);
	SDL_RenderPresent(internal_renderer);
}

void Renderer::render_play_again() {
	SDL_RenderClear(internal_renderer);
	render_play_again_internal();
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

std::tuple<int, int> Renderer::get_window_dimensions() const
{
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	return std::tuple<int, int>(w, h);
}

std::tuple<int, int> Renderer::get_tile_sprite_dimensions(Board &board)
{
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	return std::tuple<int, int>(w / board.get_width(), h / board.get_height());
}

void Renderer::render_tiles(Board &board)
{
	SDL_Rect clipping_rect;
	int sprite_screen_width = std::get<0>(get_tile_sprite_dimensions(board));
	int sprite_screen_height = std::get<1>(get_tile_sprite_dimensions(board));
	for(int row = 0; row < board.get_height(); ++row)
	{
		for(int col = 0; col < board.get_width(); ++col) {
			std::tuple<Board::Tile, int, bool> current_tile = board.get_tile(row, col);
#ifndef RENDERER_DEBUG_SHOW_ALL
			if(!std::get<2>(current_tile))
			{
				// Tile not visible render unknown
				clipping_rect.x = TILE_SPRITE_TEX_WIDTH * std::get<1>(UNKOWN_SPRITE_TEX_ROW_COL);
				clipping_rect.y = TILE_SPRITE_TEX_HEIGHT * std::get<0>(UNKOWN_SPRITE_TEX_ROW_COL);
				clipping_rect.w = TILE_SPRITE_TEX_WIDTH;
				clipping_rect.h = TILE_SPRITE_TEX_HEIGHT;
				render_tile_sprite(
					internal_renderer,
					tile_sprite_sheet,
					&clipping_rect,
					sprite_screen_width * col,
					sprite_screen_height * row,
					board);
				// Skip rendering other possibilities
				continue;
			}
#endif
			if(std::get<0>(current_tile) == Board::Tile::BOMB)
			{
				clipping_rect.x = TILE_SPRITE_TEX_WIDTH * std::get<1>(BOMB_SPRITE_TEX_ROW_COL);
				clipping_rect.y = TILE_SPRITE_TEX_HEIGHT * std::get<0>(BOMB_SPRITE_TEX_ROW_COL);
				clipping_rect.w = TILE_SPRITE_TEX_WIDTH;
				clipping_rect.h = TILE_SPRITE_TEX_HEIGHT;
				render_tile_sprite(
					internal_renderer,
					tile_sprite_sheet,
					&clipping_rect,
					sprite_screen_width * col,
					sprite_screen_height * row,
					board);
			}
			else
			{
				int adjacency = std::get<1>(current_tile);
				clipping_rect.x = TILE_SPRITE_TEX_WIDTH * std::get<1>(NUMBER_SPRITE_TEX_ROW_COL[adjacency]);
				clipping_rect.y = TILE_SPRITE_TEX_HEIGHT * std::get<0>(NUMBER_SPRITE_TEX_ROW_COL[adjacency]);
				clipping_rect.w = TILE_SPRITE_TEX_WIDTH;
				clipping_rect.h = TILE_SPRITE_TEX_HEIGHT;
				render_tile_sprite(
					internal_renderer,
					tile_sprite_sheet,
					&clipping_rect,
					sprite_screen_width * col,
					sprite_screen_height * row,
					board);
			}
		}
	}
}

void Renderer::render_board(Board &board)
{
	render_tiles(board);
	// Render grid last so tiles don't overlap it
	render_grid(board);
}

void Renderer::render_grid(Board &board)
{
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	int rows = board.get_height();
	int cols = board.get_width();

	int row_height_pixels = h / rows;
	int col_width_pixels = w / cols;

	SDL_SetRenderDrawColor(internal_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	// TODO handle errors?
	for(int i = 0; i < rows - 1; ++i)
	{
		if(SDL_RenderDrawLine(internal_renderer, 0, row_height_pixels * (i + 1), w, row_height_pixels * (i + 1)) != 0)
		{
			std::cout << "SDL_RenderDrawLine Error: " << SDL_GetError() << std::endl;
			return;
		}
		for(int j = 0; j < cols - 1; ++j)
		{
			if(SDL_RenderDrawLine(internal_renderer, col_width_pixels * (j + 1), 0, col_width_pixels * (j + 1), h) != 0)
			{
				std::cout << "SDL_RenderDrawLine Error: " << SDL_GetError() << std::endl;
				return;
			}
		}
	}
}

void Renderer::render_play_again_internal()
{
	SDL_SetRenderDrawColor(internal_renderer, 255, 255, 255, 255);
	SDL_RenderClear(internal_renderer);

	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	// Calculate clipping rect
	SDL_Rect clipping_rect;
	clipping_rect.x = 0;
	clipping_rect.y = 0;
	clipping_rect.w = PLAY_AGAIN_TEX_WIDTH;
	clipping_rect.h = PLAY_AGAIN_TEX_HEIGHT;

	render_sprite(
		internal_renderer,
		play_again_tex,
		&clipping_rect,
		w * .2f,
		h * .2f,
		w * .6f,
		h * .4f);

	clipping_rect.w = YEAH_TEX_WIDTH;
	clipping_rect.h = YEAH_TEX_HEIGHT;
	render_sprite(
		internal_renderer,
		yeah_tex,
		&clipping_rect,
		w * .2f,
		h * .6f,
		w * .3f,
		h * .3f);

	clipping_rect.w = NAH_TEX_WIDTH;
	clipping_rect.h = NAH_TEX_HEIGHT;
	render_sprite(
		internal_renderer,
		nah_tex,
		&clipping_rect,
		w * .5f,
		h * .6f,
		w * .3f,
		h * .3f);
}

void Renderer::render_sprite(
	SDL_Renderer *renderer,
	SDL_Texture *texture,
	SDL_Rect *clipping_rect,
	int x,
	int y,
	int w,
	int h
	)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.w = w;
	destination.h = h;
	SDL_RenderCopy(renderer, texture, clipping_rect, &destination);
}

void Renderer::render_tile_sprite (
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
	std::tuple<int, int> destination_dimensions = get_tile_sprite_dimensions(board);
	int w = std::get<0>(destination_dimensions);
	int h = std::get<1>(destination_dimensions);
	render_sprite(renderer, sprite_sheet, clipping_rect, x, y, w, h);
}
