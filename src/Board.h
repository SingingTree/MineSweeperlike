#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <tuple>

class Board
{
public:
	unsigned int const DIMENSION_MAX = 5000;
	enum Tile { BOMB, EMPTY };
	Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs);
	int get_width();
	int get_height();
	std::tuple<Tile, int> get_tile(int row, int col);

private:
	unsigned int board_width;
	unsigned int board_height;
	unsigned int num_bombs;
	std::vector<Tile> bomb_map;
	std::vector<int> bomb_adjacency_map;

	void setup_board_random();
	void calculate_adjacency();
	unsigned int coordinates_to_index(unsigned int row, unsigned int col);
	std::tuple<unsigned int, unsigned int> index_to_coordinates(unsigned int index);
};

#endif //BOARD_H