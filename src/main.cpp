#include <iostream>
#include <SDL.h>
#include "Board.h"

int main(int argc, char** argv)
{
	Board board(10, 10, 2);
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::cout << "SDL window could not be created: " << SDL_GetError() << std::endl;
		return 1;
	}
}