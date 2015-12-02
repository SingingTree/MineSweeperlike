#include <iostream>
#include "Board.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
	Board board(10, 10, 2);
	Renderer renderer;
	if(renderer.init() != 0)
	{
		renderer.quit();
		return 1;
	}

	bool running = true;
	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			// Close window
			if(event.type == SDL_QUIT)
			{
				running = false;
			}
			// Presses any key
			if(event.type == SDL_KEYDOWN)
			{
				running = false;
			}
			// Click the mouse
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				running = false;
			}

		}
		renderer.render();

	}

	renderer.quit();

	return 0;
}