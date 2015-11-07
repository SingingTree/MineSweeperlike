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

void Board::setup_board_random()
{
	unsigned int total_tiles = board_width * board_height;
	unsigned int num_empty_tiles = total_tiles - num_bombs;

	for(unsigned int i = 0; i < num_bombs; ++i)
	{
		tiles.push_back(Tile::BOMB);
	}
	for(unsigned int i = 0; i < num_empty_tiles; ++i)
	{
		tiles.push_back(Tile::EMPTY);
	}
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);
	std::shuffle(std::begin(tiles), std::end(tiles), engine);
}
