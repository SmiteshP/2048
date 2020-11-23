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

    look_left();
    look_up();
    look_right();
    look_down();

    update_state();
}

board::~board() { delete grid_queue; }

bool board::move_left() {
    if (next_left == curr_state) {
        return false;
    } else {
        curr_state = next_left;
        update_state();
        return true;
    }
}

bool board::move_up() {
    if (next_up == curr_state) {
        return false;
    } else {
        curr_state = next_up;
        update_state();
        return true;
    }
}

bool board::move_right() {
    if (next_right == curr_state) {
        return false;
    } else {
        curr_state = next_right;
        update_state();
        return true;
    }
}

bool board::move_down() {
    if (next_down == curr_state) {
        return false;
    } else {
        curr_state = next_down;
        update_state();
        return true;
    }
}
