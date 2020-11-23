#include "board.hpp"
#include <iostream>
// #include "state_queue.hpp"
// #include "state_queue.cpp"
using namespace std;

board::board()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr_board[i][j] = 0;
        }
    }
    add_random_tile();
    add_random_tile();
    grid_queue = new state_queue<std::array<std::array<int, 4>, 4>, 5>(curr_board);
    update_state();
    score = 0;    
}

board::~board() {
    delete(grid_queue);
}

bool board::move_left(){
    if(curr_board==next_left) return false;
    curr_board = next_left;
    add_random_tile();
    update_state();
    return true;
}

bool board::move_up(){
    if(curr_board==next_up) return false;
    curr_board = next_up;
    add_random_tile();
    update_state();
}

bool board::move_right(){
    if(curr_board==next_right) return false;
    curr_board = next_right;
    add_random_tile();
    update_state();
    return true;
}

bool board::move_down(){
    if(curr_board==next_down) return false;
    curr_board = next_down;
    add_random_tile();
    update_state();
    return true;
}

bool board::undo()
{
    if (grid_queue->can_undo())
    {
        grid_queue->undo();
        curr_board = grid_queue->get_state();
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
        curr_board = grid_queue->get_state();
        update_state(); 
        return true;
    }
    return false;
}

std::array<std::array<int, 4>, 4> board::get_curr_board(){
    return curr_board;
}

std::array<std::array<std::array<int, 4>, 4>, 4> board::get_next_states(){
    std::array<std::array<std::array<int, 4>, 4>, 4> next_states;
    next_states[0] = next_left;
    next_states[1] = next_up;
    next_states[2] = next_right;
    next_states[3] = next_down;
    return next_states;
}

int board::get_curr_max_tile(){
    return curr_max;
}

int board::get_next_max_tile(){
    return next_max;
}

int board::get_curr_sum(){
    return curr_sum;
}

bool board::next_move_possible(){
    return ( (curr_board!=next_left) | (curr_board!=next_up) | (curr_board!=next_right) | (curr_board!=next_down) );
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
    look_left();
    look_up();
    look_right();
    look_down();
    next_max = max(next_max, grid_max(next_left));
    next_max = max(next_max, grid_max(next_right));
    next_max = max(next_max, grid_max(next_up));
    next_max = max(next_max, grid_max(next_down));
    cout << curr_max << " " << next_max << " " << curr_sum << endl;
    
}