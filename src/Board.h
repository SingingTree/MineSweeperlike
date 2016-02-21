#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <tuple>

class Board
{
public:
	unsigned int const DIMENSION_MAX = 5000;
	enum Tile { BOMB, EMPTY };
	enum SelectionResult { ALREADY_SEEN, BOMBED, REVEALED };
	enum GameState { ON_GOING, LOST, WON };
	Board(unsigned int board_width, unsigned int board_height, unsigned int num_bombs);
	int get_width() const;
	int get_height() const;
	GameState get_game_state() const;
	std::tuple<Tile, int, bool> get_tile(int row, int col) const;
	SelectionResult select_tile(int row, int col);
	
private:
	unsigned int board_width;
	unsigned int board_height;
	unsigned int num_bombs;
	std::vector<Tile> bomb_map;
	std::vector<int> bomb_adjacency_map;
	std::vector<bool> visiblity_map;

	void setup_board_random(unsigned int num_bombs);
	void setup_visibility();
	void calculate_adjacency();
	void make_all_visible();
	void flood_fill_discover(unsigned int row, unsigned int col);
	unsigned int get_num_visible_tiles() const;
	unsigned int get_num_non_visible_tiles() const;
	unsigned int coordinates_to_index(unsigned int row, unsigned int col) const;
	std::tuple<unsigned int, unsigned int> index_to_coordinates(unsigned int index) const;
};

#endif //BOARD_H