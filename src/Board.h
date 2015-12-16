#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board
{
public:
	unsigned int const DIMENSION_MAX = 5000;
	enum Tile { BOMB, EMPTY };
	Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs);
	int get_width();
	int get_height();

private:
	unsigned int board_width;
	unsigned int board_height;
	unsigned int num_bombs;
	std::vector<Tile> bomb_map;
	std::vector<int> bomb_adjacency_map;

	void setup_board_random();
};

#endif //BOARD_H