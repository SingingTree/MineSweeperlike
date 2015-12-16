#include <algorithm>
#include <random>
#include <chrono>
#include "Board.h"

Board::Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs) :
	board_width(board_width > DIMENSION_MAX ? DIMENSION_MAX : board_width),
	board_height(board_height > DIMENSION_MAX ? DIMENSION_MAX : board_height),
	num_bombs(num_bombs)
{
	// Make sure we don't have too many bombs
	if(this->num_bombs > this->board_width * this->board_height)
	{
		this->num_bombs = this->board_width * this->board_height - 1;
	}
	setup_board_random();
}

int Board::get_width()
{
	return board_width;
}

int Board::get_height()
{
	return board_height;
}

void Board::setup_board_random()
{
	unsigned int total_tiles = board_width * board_height;
	unsigned int num_empty_tiles = total_tiles - num_bombs;

	// Calculate bomb locations
	for(unsigned int i = 0; i < num_bombs; ++i)
	{
		bomb_map.push_back(Tile::BOMB);
	}
	for(unsigned int i = 0; i < num_empty_tiles; ++i)
	{
		bomb_map.push_back(Tile::EMPTY);
	}
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);
	std::shuffle(std::begin(bomb_map), std::end(bomb_map), engine);
	// Done calculating bomb locations

	// Calculate adjacency
	int adjacent_bombs, row, col, adjusted_index;
	for(unsigned int i = 0; i < total_tiles; ++i)
	{
		adjacent_bombs = 0;
		row = i / board_width;
		col = i % board_width;
		for(int j = -1; j <= 1; ++j)
		{
			for(int k = -1; k <= 1; ++k)
			{
				if(row + j < 0 || row + j >= board_height)
				{
					break;
				}
				if(col + k < 0 || col + k >= board_width)
				{
					continue;
				}
				adjusted_index = i + (j * board_width) + k;
				if(bomb_map.at(adjusted_index) == Tile::BOMB)
				{
					++adjacent_bombs;
				}
			}
			bomb_adjacency_map.push_back(adjacent_bombs);
		}
	}
	// Done calculating adjacency
}
