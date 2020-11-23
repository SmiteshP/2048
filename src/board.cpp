#include "board.hpp"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

board::board()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr_board[i][j] = 0;
        }
    }
    // add_random_tile();
    // add_random_tile();
    score = 0; 
    grid_queue = new state_queue<std::array<std::array<int, 4>, 4>, 10>(curr_board);
    score_queue = new state_queue<int, 10>(score);
    
    update_state();
       
}

board::~board() {
    delete(grid_queue);
    delete(score_queue);
}

bool board::move_left(){
    if(curr_board==next_left) {
        return false;
    }
    curr_board = next_left;
    score += score_increment_left;
    // add_random_tile();
    update_state();
    return true;
}

bool board::move_up(){
    if(curr_board==next_up) {
        return false;
    }
    curr_board = next_up;
    score += score_increment_up;
    // add_random_tile();
    update_state();
    return true;
}

bool board::move_right(){
    if(curr_board==next_right) {
        return false;
    }
    curr_board = next_right;
    score += score_increment_right;
    // add_random_tile();
    update_state();
    return true;
}

bool board::move_down(){
    if(curr_board==next_down) {
        return false;
    }
    curr_board = next_down;
    score += score_increment_down;
    // add_random_tile();
    update_state();
    return true;
}

bool board::undo()
{
    if (grid_queue->can_undo())
    {
        grid_queue->undo();
        score_queue->undo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state();
        return true;
    }
    return false;
}

bool board::redo()
{
    if (grid_queue->can_redo())
    {
        grid_queue->redo();
        score_queue->redo();
        curr_board = grid_queue->get_state();
        score = score_queue->get_state();
        update_state(); 
        return true;
    }
    return false;
}

std::array<std::array<int, 4>, 4> board::get_curr_board() const{
    return curr_board;
}

std::array<std::array<std::array<int, 4>, 4>, 4> board::get_next_states() const{
    // std::array<std::array<std::array<int, 4>, 4>, 4> next_states;
    // next_states[0] = next_left;
    // next_states[1] = next_up;
    // next_states[2] = next_right;
    // next_states[3] = next_down;
    // return next_states;
    return {next_left, next_up, next_right, next_down};
}

int board::get_curr_max_tile() const{
    return curr_max;
}

int board::get_next_max_tile() const{
    return next_max;
}

int board::get_curr_sum() const{
    return curr_sum;
}

bool board::next_move_possible() const{
    return ( (curr_board!=next_left) || (curr_board!=next_up) || (curr_board!=next_right) || (curr_board!=next_down) );
}

int board::grid_max(const std::array<std::array<int, 4>, 4> &arr){
    int gm = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gm = max(gm, arr[i][j]);
        }
    }
    return gm;
}

void board::update_state()
{
    curr_max = 0;
    curr_sum = 0;
    next_max = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr_sum += curr_board[i][j];
            if (curr_board[i][j] > curr_max)
                curr_max = curr_board[i][j];
        }
    }
    // look_left();
    // look_up();
    // look_right();
    // look_down();
    next_max = max(next_max, grid_max(next_left));
    next_max = max(next_max, grid_max(next_right));
    next_max = max(next_max, grid_max(next_up));
    next_max = max(next_max, grid_max(next_down));
    cout << curr_max << " " << next_max << " " << curr_sum << endl;
    return;
    
}