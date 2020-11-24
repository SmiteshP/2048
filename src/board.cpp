#include <chrono>
#include <random>
#include <iostream>
#include <vector>

#include "board.hpp"

using namespace std;

board::board() {
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            curr_board[i][j] = 0;
        }
    }

    add_random_tile();
    add_random_tile();

    score = 0;
    score_increment_left = 0;
    score_increment_right = 0;
    score_increment_up = 0;
    score_increment_down = 0;

    grid_queue =
        new state_queue<std::array<std::array<int, 4>, 4>, 10>(curr_board);
    score_queue = new state_queue<int, 10>(score);

    update_state();
}

board::~board() {
    delete grid_queue;
    delete score_queue;
}

bool board::move_left() {
    if (curr_board == next_left) {
        return false;
    }
    curr_board = next_left;
    score += score_increment_left;
    add_random_tile();
    update_state();
    grid_queue->push(curr_board);
    score_queue->push(score);
    return true;
}

bool board::move_up() {
    if (curr_board == next_up) {
        return false;
    }
    curr_board = next_up;
    score += score_increment_up;
    add_random_tile();
    update_state();
    grid_queue->push(curr_board);
    score_queue->push(score);
    return true;
}

bool board::move_right() {
    if (curr_board == next_right) {
        return false;
    }
    curr_board = next_right;
    score += score_increment_right;
    add_random_tile();
    update_state();
    grid_queue->push(curr_board);
    score_queue->push(score);
    return true;
}

bool board::move_down() {
    if (curr_board == next_down) {
        return false;
    }
    curr_board = next_down;
    score += score_increment_down;
    add_random_tile();
    update_state();
    grid_queue->push(curr_board);
    score_queue->push(score);
    return true;
}

bool board::undo() {
    if (grid_queue->can_undo()) {
        grid_queue->undo();
        score_queue->undo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state();
        return true;
    }
    return false;
}

bool board::redo() {
    if (grid_queue->can_redo()) {
        grid_queue->redo();
        score_queue->redo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state();
        return true;
    }
    return false;
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

bool board::next_left_possible() const { return (curr_board != next_left); }

bool board::next_up_possible() const { return (curr_board != next_up); }

bool board::next_right_possible() const { return (curr_board != next_right); }

bool board::next_down_possible() const { return (curr_board != next_down); }

int board::collapse(std::array<int*, 4> arr) {
    int score_increment = 0;

    // shift
    for (int i = 3; i > 0; i--) {
        if (*arr[i] == 0 && *arr[i - 1] != 0) {
            std::swap(*arr[i], *arr[i - 1]);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (*arr[i] != 0 && *arr[i + 1] == 0) {
            std::swap(*arr[i], *arr[i + 1]);
        }
    }

    // merge
    for (int i = 3; i > 0; i--) {
        if (*arr[i] != 0 && *arr[i] == *arr[i - 1]) {
            *arr[i] += *arr[i - 1];
            score_increment += *arr[i - 1];
            *arr[i - 1] = 0;
            i--;
        }
    }

    // shift
    for (int i = 3; i > 0; i--) {
        if (*arr[i] == 0 && *arr[i - 1] != 0) {
            std::swap(*arr[i], *arr[i - 1]);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (*arr[i] != 0 && *arr[i + 1] == 0) {
            std::swap(*arr[i], *arr[i + 1]);
        }
    }

    return score_increment;
}

void board::look_left() {
    next_left = curr_board;
    collapse({&next_left[0][3], &next_left[0][2], &next_left[0][1],
              &next_left[0][0]});
    collapse({&next_left[1][3], &next_left[1][2], &next_left[1][1],
              &next_left[1][0]});
    collapse({&next_left[2][3], &next_left[2][2], &next_left[2][1],
              &next_left[2][0]});
    collapse({&next_left[3][3], &next_left[3][2], &next_left[3][1],
              &next_left[3][0]});
}

void board::look_up() {
    next_up = curr_board;
    collapse({&next_up[3][0], &next_up[2][0], &next_up[1][0], &next_up[0][0]});
    collapse({&next_up[3][1], &next_up[2][1], &next_up[1][1], &next_up[0][1]});
    collapse({&next_up[3][2], &next_up[2][2], &next_up[1][2], &next_up[0][2]});
    collapse({&next_up[3][3], &next_up[2][3], &next_up[1][3], &next_up[0][3]});
}

void board::look_right() {
    next_right = curr_board;
    collapse({&next_right[0][0], &next_right[0][1], &next_right[0][2],
              &next_right[0][3]});
    collapse({&next_right[1][0], &next_right[1][1], &next_right[1][2],
              &next_right[1][3]});
    collapse({&next_right[2][0], &next_right[2][1], &next_right[2][2],
              &next_right[2][3]});
    collapse({&next_right[3][0], &next_right[3][1], &next_right[3][2],
              &next_right[3][3]});
}

void board::look_down() {
    next_down = curr_board;
    collapse({&next_down[0][0], &next_down[1][0], &next_down[2][0],
              &next_down[3][0]});
    collapse({&next_down[0][1], &next_down[1][1], &next_down[2][1],
              &next_down[3][1]});
    collapse({&next_down[0][2], &next_down[1][2], &next_down[2][2],
              &next_down[3][2]});
    collapse({&next_down[0][3], &next_down[1][3], &next_down[2][3],
              &next_down[3][3]});
}

bool board::add_random_tile() {
    int tile_val = rand() % 10 == 0 ? 4 : 2;
    int blank_cnt = 0;

    vector<pair<int, int>> v;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (curr_board[i][j] == 0) {
                v.push_back(make_pair(i, j));
                blank_cnt++;
            }
        }
    }

    if (blank_cnt == 0) {
        return false;
    }

    int tile_index = rand() % blank_cnt;
    int i = v[tile_index].first;
    int j = v[tile_index].second;
    curr_board[i][j] = tile_val;
    return true;
}

int board::grid_max(const std::array<std::array<int, 4>, 4>& arr) {
    int gm = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gm = std::max(gm, arr[i][j]);
        }
    }
    return gm;
}

void board::update_state() {
    curr_max = 0;
    curr_sum = 0;
    next_max = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            curr_sum += curr_board[i][j];
            if (curr_board[i][j] > curr_max) curr_max = curr_board[i][j];
        }
    }
    look_left();
    look_up();
    look_right();
    look_down();
    next_max = std::max(next_max, grid_max(next_left));
    next_max = std::max(next_max, grid_max(next_right));
    next_max = std::max(next_max, grid_max(next_up));
    next_max = std::max(next_max, grid_max(next_down));
    return;
}
