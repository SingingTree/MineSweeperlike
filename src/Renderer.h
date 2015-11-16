#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

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
};

#endif //RENDERER_H