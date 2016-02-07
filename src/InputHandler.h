#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <tuple>

class InputHandler
{
public:
	std::tuple<int, int> row_col_from_click_coordinates(
		int number_rows,
		int number_cols,
		std::tuple<int, int> &window_dimensions,
		std::tuple<int, int> &click_position);
};

#endif