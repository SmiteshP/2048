#pragma once

#include "state_queue.hpp"
#include "state_queue.cpp"

#include <array>
#include <map>

class board {
 public:
    // Constructor and Destructor
    board();
    ~board();

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

    // get curr_board
    std::array<std::array<int, 4>, 4> get_curr_board() const;

    // Return next states of the board
    // Order : left, up, right, down
    std::array<std::array<std::array<int, 4>, 4>, 4> get_next_states() const;

    // Return max tile on current board
    int get_curr_max_tile() const;

    // Return maximum tile attainable in one move
    int get_next_max_tile() const;

    // Return current board sum
    int get_curr_sum() const;

    // check if performing any move will change the board
    // true if some move is possible, else false and board has reached dead end

    bool next_left_possible() const;
    bool next_up_possible() const;
    bool next_right_possible() const;
    bool next_down_possible() const;

 private:
    std::array<std::array<int, 4>, 4> curr_board;

    std::array<std::array<int, 4>, 4> next_left;
    std::array<std::array<int, 4>, 4> next_up;
    std::array<std::array<int, 4>, 4> next_right;
    std::array<std::array<int, 4>, 4> next_down;

    int score_increment_left;
    int score_increment_up;
    int score_increment_right;
    int score_increment_down;

    //  std::map<int, int> curr_tile_cnt;

    int curr_max;
    int next_max;
    int curr_sum;

    int score;

    // store game board history
    state_queue<std::array<std::array<int, 4>, 4>, 10> *grid_queue;

    // store score infomation at each point
    state_queue<int, 10> *score_queue;

    // collapse the list of numbers from left to right
    // returns increment in score
    int collapse(std::array<int *, 4> arr);

    // update value of respective move without adding random tile
    void look_left();
    void look_up();
    void look_right();
    void look_down();

    // Randomly add tile
    // return true if tile added successfully
    // return false if tile cannot be added
    bool add_random_tile();

    // Calculate max of the given grid
    int grid_max(const std::array<std::array<int, 4>, 4> &arr);

    // Calculates the diffent state->Z operations on curr_state
    // Max tile
    // Sum
    // Set of tiles and their count
    void update_state();
};
