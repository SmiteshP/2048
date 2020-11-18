#include "board.hpp"

board::board()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curr_board[i][j] = 0;
        }
    }

    add_random_tile(curr_board);
}
