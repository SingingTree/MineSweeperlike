#include "InputHandler.h"

std::tuple<int, int> InputHandler::row_col_from_click_coordinates(int number_rows, int number_cols, std::tuple<int, int>& window_dimensions, std::tuple<int, int>& click_position)
{
	int sprite_w = std::get<0>(window_dimensions) / number_cols;
	int sprite_h = std::get<1>(window_dimensions) / number_rows;

	int row = std::get<0>(click_position) / sprite_w;
	int col = std::get<1>(click_position) / sprite_h;

	return std::tuple<int, int>(row, col);
}
