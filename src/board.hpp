#pragma once

#include <array>

class board {
public:
	// return value of respective move without adding random tile
	std::array<std::array <int, 4>, 4> look_left();
	std::array<std::array <int, 4>, 4> look_up();
	std::array<std::array <int, 4>, 4> look_right();
	std::array<std::array <int, 4>, 4> look_down();

	// make respective move
	// return true if successful else false
	bool move_left();
	bool move_up();
	bool move_right();
	bool move_down();

	// undo and redo
	// return true if successful else false
	bool undo();
	bool redo();

private:
	// stores the current state of board
	std::array <std::array <int, 4>, 4> curr_board;

	// stores immediate next board states
	std::array <std::array <int, 4>, 4> next_left;
	std::array <std::array <int, 4>, 4> next_up;
	std::array <std::array <int, 4>, 4> next_right;
	std::array <std::array <int, 4>, 4> next_down;

	int curr_max;
	int next_max;
	int curr_sum;

	// store game board history
	state_queue <std::array <std::array <int, 4>, 4>> grid;
	// store random numbers to compute/recompute board
	state_queue <std::pair <int, int>> random_numbers;

	// collapse the list of numbers from left to right
	void collapse(std::array<int *, 4> arr);

	// Randomly add tile
	// return true if tile added successfully
	// return false if tile cannot be added
	bool add_random_tile(std::array <std::array <int, 4>, 4>& grid);

	// Calculate max of next states
	void next_grid_max();

	// Calculates the diffent state->Z operations on curr_state
	// Max tile
	// Sum
	// Set of tiles and their count
	void update_state(const std::array <std::array <int, 4>, 4>& grid);
};
