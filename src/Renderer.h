#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>

class Renderer
{
public:
	Renderer();
	int init();
	void render();
	void quit();
	
private:
	SDL_Window *window;
	SDL_Renderer *internal_renderer;
	SDL_Texture *tile_sprite_sheet;

	void render_sprite(
		SDL_Renderer *renderer,
		SDL_Texture *sprite_sheet,
		SDL_Rect *clipping_rect,
		int x,
		int y);
};

#endif //RENDERER_H