#include <iostream>
#include "Board.h"
#include "Renderer.h"
#include "InputHandler.h"

int main(int argc, char** argv)
{
	Board board(10, 10, 2);
	Renderer renderer;
	InputHandler inputHandler;
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
				std::tuple<int, int> click_pos(event.button.x, event.button.y);
				std::tuple<int, int> row_and_col = inputHandler.row_col_from_click_coordinates(
					board.get_height(),
					board.get_width(),
					renderer.get_window_dimensions(),
					click_pos
					);
				board.select_tile(std::get<0>(row_and_col), std::get<1>(row_and_col));
				std::cout << std::get<0>(row_and_col) << ", " << std::get<1>(row_and_col) << std::endl;
			}

		}
		std::cout << board.get_game_state() << std::endl;
		renderer.render(board);

	}

	renderer.quit();

	return 0;
}