#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <tuple>

class InputHandler
{
public:
	enum Action {QUIT};
	Action handle_key(SDL_Event &key_event);
	std::tuple<int, int> row_col_from_click_coordinates(
		int number_rows,
		int number_cols,
		std::tuple<int, int> &window_dimensions,
		SDL_Event &click_event);
};

#endif