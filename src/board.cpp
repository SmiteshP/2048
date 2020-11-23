#include <chrono>
#include <random>
#include "board.hpp"

board::board() {
    // seed random number generator
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());

    curr_board = {{0}};

    // initial 2 random tiles
    add_random_tile();
    add_random_tile();

    grid_queue =
        new state_queue<std::array<std::array<int, 4>, 4>, 10>(curr_board);
    score_queue = new state_queue<int, 10>(0);

    update_state();
}

board::~board() {
    delete grid_queue;
    delete score_queue;
}

bool board::move_left() {
    if (next_left == curr_board) {
        return false;
    } else {
        curr_board = next_left;
        score += score_increment_left;
        update_state();
        return true;
    }
}

bool board::move_up() {
    if (next_up == curr_board) {
        return false;
    } else {
        curr_board = next_up;
        score += score_increment_up;
        update_state();
        return true;
    }
}

bool board::move_right() {
    if (next_right == curr_board) {
        return false;
    } else {
        curr_board = next_right;
        score += score_increment_right;
        update_state();
        return true;
    }
}

bool board::move_down() {
    if (next_down == curr_board) {
        return false;
    } else {
        curr_board = next_down;
        score += score_increment_down;
        update_state();
        return true;
    }
}

bool board::undo() {
    if (!grid_queue->can_undo()) {
        return false;
    } else {
        grid_queue->undo();
        score_queue->undo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state();
        return true;
    }
}

bool board::redo() {
    if (!grid_queue->can_redo()) {
        return false;
    } else {
        grid_queue->redo();
        score_queue->redo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state();
        return true;
    }
}

std::array<std::array<int, 4>, 4> board::get_curr_board() const {
    return curr_board;
}

std::array<std::array<std::array<int, 4>, 4>, 4> board::get_next_states()
    const {
    return {next_left, next_up, next_right, next_down};
}

int board::get_curr_max_tile() const { return curr_max; }

int board::get_next_max_tile() const { return next_max; }

int board::get_curr_sum() const { return curr_sum; }

bool board::next_move_possible() const {
    return (curr_board != next_left) || (curr_board != next_up) ||
           (curr_board != next_right) || (curr_board != next_left);
}

int board::collapse(std::array<int *, 4> arr) {
    int score_increment;

    for (int i = 3; i > 0; i--) {
        if (*arr[i] == *arr[i - 1]) {
            *arr[i] += *arr[i - 1];
            score_increment += *arr[i - 1];
            *arr[i - 1] = 0;
        }
    }

    for (int i = 2; i > 0; i--) {
        for (int j = i; j < 3; j++) {
            if (*arr[j + 1] == 0) {
                std::swap(*arr[j], *arr[j + 1]);
            }
        }
    }

    return score_increment;
}

bool board::add_random_tile() { return false; }

void board::update_state() { return; }
