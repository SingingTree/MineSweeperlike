#include <iostream>
#include "Board.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
	Board board(10, 10, 2);
	Renderer renderer;
	if(renderer.init() != 0)
	{
		return 1;
	}

	for(int i = 0; i < 5; ++i)
	{
		renderer.render();
		SDL_Delay(1000);
	}

	renderer.quit();

	return 0;
}