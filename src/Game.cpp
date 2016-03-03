#include "Game.h"

Game::Game() : board(10, 10, 2), renderer(), gameState(IN_GAME)
{
}

int Game::init()
{
	// Handle renderer setup
	if(renderer.init() != 0)
	{
		renderer.quit();
		return 1;
	}

	return 0;
}

// Returns a bool indicating if the game should continue (true) or terminate (false)
bool Game::handle_input(SDL_Event &event)
{
	// Close window
	if(event.type == SDL_QUIT)
	{
		return false;
	}
	// Presses any key
	if(event.type == SDL_KEYDOWN)
	{
		switch(inputHandler.handle_key(event))
		{
		case InputHandler::Action::QUIT:
			return false;
		}
	}
	// Click the mouse
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::tuple<int, int> row_and_col = inputHandler.row_col_from_click_coordinates(
			board.get_height(),
			board.get_width(),
			renderer.get_window_dimensions(),
			event
			);
		board.select_tile(std::get<0>(row_and_col), std::get<1>(row_and_col));
	}
	return true;
}

int Game::main_loop()
{
	bool running = true;
	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			running = handle_input(event);
		}
		renderer.render_in_game(board);
	}

	return 0;
}
