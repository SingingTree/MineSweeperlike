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
	
private:
	SDL_Window* window;
	SDL_Renderer *internal_renderer;
};

#endif //RENDERER_H