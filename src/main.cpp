#include <iostream>
#include "Board.h"
#include "Renderer.h"
#include "InputHandler.h"

// Returns a bool indicating if the game should continue (true) or terminate (false)
bool game_handle_input(SDL_Event &event, Renderer &renderer, Board &board, InputHandler &inputHandler)
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
		std::cout << std::get<0>(row_and_col) << ", " << std::get<1>(row_and_col) << std::endl;
	}
	return true;
}

void game_loop(Renderer &renderer, Board &board)
{
	InputHandler inputHandler;
	bool running = true;
	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			running = game_handle_input(event, renderer, board, inputHandler);
		}
		std::cout << board.get_game_state() << std::endl;
		renderer.render(board);
	}
}

int game()
{
	// Setup board
	Board board(10, 10, 2);
	// Setup renderer
	Renderer renderer;
	// Handle renderer setup
	if(renderer.init() != 0)
	{
		renderer.quit();
		return 1;
	}

	// If we've made it this far we can start the game!
	game_loop(renderer, board);

	// Once game's done destory our renderer
	renderer.quit();

	return 0;
}

int main(int argc, char** argv)
{
	return game();
}