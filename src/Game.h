#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Renderer.h"
#include "InputHandler.h"

class Game
{
public:
	Game();
	// Initialise SDL components (renderer)
	int init();
	// Main game loop, will return when game is terminating
	int main_loop();

private:
	Board board;
	Renderer renderer;
	InputHandler inputHandler;

	bool handle_input(SDL_Event &event);
};

#endif // GAME_H
