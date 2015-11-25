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

	SDL_Renderer* get_internal_renderer();
	
private:
	SDL_Window *window;
	SDL_Renderer *internal_renderer;
	SDL_Surface *window_surface;
	SDL_Surface *tile_sprite_sheet;
};

#endif //RENDERER_H