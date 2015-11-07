#include <vector>

class Board
{
public:
	unsigned int const DIMENSION_MAX = 5000;
	enum Tile { BOMB, EMPTY };
	Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs);

private:
	unsigned int board_width;
	unsigned int board_height;
	unsigned int num_bombs;
	std::vector<Tile> tiles;

	void setup_board_random();
};
