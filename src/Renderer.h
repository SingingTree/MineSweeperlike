#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <tuple>
#include "Board.h"

class Renderer
{
public:
	int const SPRITE_TEX_WIDTH = 256;
	int const SPRITE_TEX_HEIGHT = 256;
	std::tuple<int, int> const number_sprite_row_col[9] = {
		std::tuple<int, int>(2, 3),
		std::tuple<int, int>(0, 0),
		std::tuple<int, int>(0, 1),
		std::tuple<int, int>(0, 2),
		std::tuple<int, int>(0, 3),
		std::tuple<int, int>(1, 0),
		std::tuple<int, int>(1, 1),
		std::tuple<int, int>(1, 2),
		std::tuple<int, int>(1, 3)
	};
	std::tuple<int, int> const bomb_sprite_row_col = std::tuple<int, int>(2, 0);
	std::tuple<int, int> const unknown_sprite_row_col = std::tuple<int, int>(2, 1);

	Renderer();
	int init();
	void render(Board &board);
	void quit();
	
private:
	SDL_Window *window;
	SDL_Renderer *internal_renderer;
	SDL_Texture *tile_sprite_sheet;

	std::tuple<int, int> get_sprite_dimensions(Board &board);
	void render_board(Board &board);
	void render_tiles(Board &board);
	void render_grid(Board &board);
	void render_sprite(
		SDL_Renderer *renderer,
		SDL_Texture *sprite_sheet,
		SDL_Rect *clipping_rect,
		int x,
		int y,
		Board &board);
};

#endif //RENDERER_H