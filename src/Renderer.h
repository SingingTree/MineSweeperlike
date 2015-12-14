#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <tuple>
#include "Board.h"

class Renderer
{
public:
	Renderer();
	int init();
	void render(Board &board);
	void quit();
	
private:
	SDL_Window *window;
	SDL_Renderer *internal_renderer;
	SDL_Texture *tile_sprite_sheet;

	std::tuple<int, int> get_sprite_dimensions(Board &board);
	void render_board(SDL_Renderer *renderer, Board &board);
	void render_sprite(
		SDL_Renderer *renderer,
		SDL_Texture *sprite_sheet,
		SDL_Rect *clipping_rect,
		int x,
		int y,
		Board &board);
};

#endif //RENDERER_H