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
	SDL_Texture *sprites = 

	for(int i = 0; i < 5; ++i)
	{
		renderer.render();
		SDL_Delay(1000);
	}

	renderer.quit();

	return 0;
}