#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>
#include "Board.h"

Board::Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs) :
	board_width(board_width > DIMENSION_MAX ? DIMENSION_MAX : board_width),
	board_height(board_height > DIMENSION_MAX ? DIMENSION_MAX : board_height),
	num_bombs(num_bombs),
	reroll_board_if_first_move_is_bomb(true)
{
	// Make sure we don't have too many bombs
	if(this->num_bombs > this->board_width * this->board_height)
	{
		this->num_bombs = this->board_width * this->board_height - 1;
	}
	setup_board();
}

int Board::get_width() const
{
	return board_width;
}

int Board::get_height() const
{
	return board_height;
}

std::tuple<Board::Tile, int, bool> Board::get_tile(int row, int col) const
{
	size_t index = coordinates_to_index(row, col);
	return std::tuple<Board::Tile, int, bool>(bomb_map.at(index),
										bomb_adjacency_map.at(index),
										visiblity_map.at(index));
}

Board::SelectionResult Board::select_tile(int row, int col)
{
	int unsigned index = coordinates_to_index(row, col);
	if(visiblity_map.at(index))
	{
		return SelectionResult::ALREADY_SEEN;
	}
	
	if(bomb_map.at(index) == Tile::BOMB)
	{
		if(reroll_board_if_first_move_is_bomb && get_num_visible_tiles() == 0)
		{
			// If it's the first move and rerolls are enabled
			while(bomb_map.at(index) == Tile::BOMB)
			{
				setup_board();
			}
		}
		else
		{
			make_all_visible();
			return SelectionResult::BOMBED;
		}
	}
	visiblity_map.at(index) = true;
	flood_fill_discover(row, col);
}

Board::GameState Board::get_game_state() const
{
	if(get_num_non_visible_tiles() == num_bombs)
	{
		return GameState::WON;
	}
	return GameState::ON_GOING;
}

void Board::calculate_adjacency() {
	bomb_adjacency_map.clear();
	unsigned int total_tiles = board_width * board_height;

	unsigned int adjacent_bombs, row, col, adjusted_index;
	for(unsigned int i = 0; i < total_tiles; ++i)
	{
		adjacent_bombs = 0;
		std::tuple<unsigned int, unsigned int> row_col = index_to_coordinates(i);
		row = std::get<0>(row_col);
		col = std::get<1>(row_col);
		for(int j = -1; j <= 1; ++j)
		{
			if(row + j < 0 || row + j >= (signed)board_height)
			{
				continue;
			}
			for(int k = -1; k <= 1; ++k)
			{
				if(col + k < 0 || col + k >= (signed)board_width)
				{
					continue;
				}
				adjusted_index = coordinates_to_index(row + j, col + k);
				if(bomb_map.at(adjusted_index) == Tile::BOMB)
				{
					++adjacent_bombs;
				}
			}
		}
		bomb_adjacency_map.push_back(adjacent_bombs);
	}
	// Done calculating adjacency
}

void Board::setup_board()
{
	setup_visibility();
	setup_board_random(num_bombs);
	calculate_adjacency();
}

void Board::make_all_visible()
{
	for(auto iter = visiblity_map.begin(); iter != visiblity_map.end(); ++iter)
	{
		*iter = true;
	}
}

void Board::flood_fill_discover(unsigned int row, unsigned int col)
{
	std::vector<std::tuple<unsigned int, unsigned int>> frontier;
	frontier.push_back(std::tuple<unsigned int, unsigned int>(row, col));

	unsigned int current_row, current_col, current_index, adjusted_index;
	bool current_has_zero_adjascent_bombs;
	std::tuple<unsigned int, unsigned int> current_row_col;

	while(!frontier.empty())
	{
		current_row_col = frontier.back();
		frontier.pop_back();
		current_row = std::get<0>(current_row_col);
		current_col = std::get<1>(current_row_col);
		current_index = coordinates_to_index(current_row, current_col);
		current_has_zero_adjascent_bombs = bomb_adjacency_map.at(current_index) == 0;

		for(int i = -1; i <= 1; ++i)
		{
			if(current_row + i < 0 || current_row + i >= (signed)board_height)
			{
				continue;
			}
			for(int j = -1; j <= 1; ++j)
			{
				if(current_col + j < 0 || current_col + j >= (signed)board_width)
				{
					continue;
				}
				adjusted_index = coordinates_to_index(
					current_row + i, current_col + j);
				if(visiblity_map.at(adjusted_index))
				{
					// Already visible, and should have been flood filled
					continue;
				}
				if(current_has_zero_adjascent_bombs)
				{
					// Can fill with 8 adjacency
					visiblity_map.at(adjusted_index) = true;
					frontier.push_back(std::tuple<unsigned int, unsigned int>(
						current_row + i,
						current_col + j));
				}
				else
				{
					// Fill with 4 adjacency
					if(i + j == 1 || i + j == -1)
					{
						// Only reveal 0 adjacent neighbours
						if(bomb_adjacency_map.at(adjusted_index) == 0)
						{
							visiblity_map.at(adjusted_index) = true;
							frontier.push_back(std::tuple<unsigned int, unsigned int>(
								current_row + i,
								current_col + j));
						}
					}
				}
			}
		}
	}
}

unsigned int Board::get_num_visible_tiles() const
{
	auto sum_trues = [](unsigned int a, bool b) {return a + (b ? 1u : 0u); };
	return std::accumulate(visiblity_map.begin(), visiblity_map.end(), 0u, sum_trues);
}

unsigned int Board::get_num_non_visible_tiles() const
{
	return visiblity_map.size() - get_num_visible_tiles();
}

unsigned int Board::coordinates_to_index(unsigned int row, unsigned int col) const
{
	return row * board_width + col;
}

std::tuple<unsigned int, unsigned int> Board::index_to_coordinates(unsigned int index) const
{
	unsigned int row = index / board_width;
	unsigned int col = index % board_width;
	return std::tuple<unsigned int, unsigned int>(row, col);
}

void Board::setup_board_random(unsigned int num_bombs)
{
	bomb_map.clear();
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
}

void Board::setup_visibility()
{
	visiblity_map.clear();
	unsigned int total_tiles = board_width * board_height;
	for(unsigned int i = 0; i < total_tiles; ++i)
	{
		visiblity_map.push_back(false);
	}
}
