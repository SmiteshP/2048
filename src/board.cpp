#include "board.hpp"
#include <iostream>
// #include "state_queue.hpp"
// #include "state_queue.cpp"

board::board()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr_board[i][j] = 0;
        }
    }
    grid.push(curr_board);
    update_state();
    // add_random_tile(curr_board);
}

board::~board() = default;

void board::print_grid() const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << curr_board[i][j] << " ";
        }
        cout << endl;
    }
}

bool board::undo()
{
    if (grid.can_undo())
    {
        grid.undo();
        curr_board = grid.get_state();
        if (grid.get_size() > 0)
        {
            update_state();
            print_grid();
        }
        return true;
    }
    return false;
}

bool board::redo()
{
    if (grid.can_redo())
    {
        grid.redo();
        curr_board = grid.get_state();

        if (grid.get_size() > 0)
        {
            update_state();
            print_grid();
        }
        return true;
    }
    return false;
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
    cout << curr_max << " " << next_max << " " << curr_sum << endl;
}