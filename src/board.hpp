#pragma once

#include <array>

class board {
public:
	// return value of repective move without adding random tile
	std::array<std::array <int, 4>, 4> look_left();
	std::array<std::array <int, 4>, 4> look_up();
	std::array<std::array <int, 4>, 4> look_right();
	std::array<std::array <int, 4>, 4> look_down();

	// make respective move
	void move_left();
	void move_up();
	void move_right();
	void move_down();

	// undo and redo
	// return true if succesful else false
	void undo();
	void redo();

private:
	// store game board history
	state_queue <std::array <std::array <int, 4>, 4>> grid;
	// store random numbers to compute/recompute board
	state_queue <std::pair <int, int>> random_numbers;

	// colapse the list of numbers from left to right
	void colapse(std::array<int *, 4> arr);
};
