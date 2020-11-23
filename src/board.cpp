#include <chrono>
#include <random>
#include "board.hpp"

board::board() {
    // seed random number generator
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // initial 2 random tiles
    add_random_tile();
    add_random_tile();

    grid_queue = new state_queue(curr_state);
    score_queue = new state_queue(0);

    update_state();
}

board::~board() {
    delete grid_queue;
    delete score_queue;
}

bool board::move_left() {
    if (next_left == curr_state) {
        return false;
    } else {
        curr_state = next_left;
		score += score_increment_left;
        update_state();
        return true;
    }
}

bool board::move_up() {
    if (next_up == curr_state) {
        return false;
    } else {
        curr_state = next_up;
		score += score_increment_up;
        update_state();
        return true;
    }
}

bool board::move_right() {
    if (next_right == curr_state) {
        return false;
    } else {
        curr_state = next_right;
		score += score_increment_right;
        update_state();
        return true;
    }
}

bool board::move_down() {
    if (next_down == curr_state) {
        return false;
    } else {
        curr_state = next_down;
		score += score_increment_down;
        update_state();
        return true;
    }
}

bool board::undo() {
    if (!grid_queue.can_undo()) {
        return false;
    } else {
        grid_queue.undo();
		score_queue.undo();
        curr_state = grid_queue.get_state();
		score = score_queue.get_state();
        update_state();
        return true;
    }
}

bool board::redo() {
    if (!grid_queue.can_redo()) {
        return false;
    } else {
        grid_queue.redo();
		score_queue.redo();
        curr_state = grid_queue.get_state();
		score = score_queue.get_state();
        update_state();
        return true;
    }
}

std::array<std::array<int, 4>, 4> board::get_curr_board() const {
	return curr_state;
}

std::array<std::array<std::array<int, 4>, 4>, 4> board::get_next_states() const {
	return {next_left, next_up, next_right, next_down};
}

int board::get_curr_max_tile() const {
	return curr_max;
}

int board::get_next_max_tile() const {
	return next_max;
}

int board::get_curr_sum() const {
	return curr_sum;
}

bool board::next_move_possible() const {
	return (curr_state != next_left) || (curr_state != next_up) || (curr_state != next_right) || (curr_state != next_left);
}
