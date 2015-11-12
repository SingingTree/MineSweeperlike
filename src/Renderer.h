#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer
{
public:
	Renderer();
	int init();
	void quit();
	
private:
	SDL_Window* window;
};

#endif //RENDERER_H