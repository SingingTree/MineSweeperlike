#include <SDL.h>
#include "InputHandler.h"

InputHandler::Action InputHandler::handle_key(SDL_Event &event)
{
	return Action::QUIT;
}

std::tuple<int, int> InputHandler::row_col_from_click_coordinates(int number_rows, int number_cols, std::tuple<int, int>& window_dimensions, SDL_Event &click_event)
{
	int sprite_w = std::get<0>(window_dimensions) / number_cols;
	int sprite_h = std::get<1>(window_dimensions) / number_rows;

	int row = click_event.button.y / sprite_h;
	int col = click_event.button.x / sprite_w;

	return std::tuple<int, int>(row, col);
}
