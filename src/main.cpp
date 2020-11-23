#include <iostream>
#include <vector>

// #include "state_queue.hpp"
// #include "state_queue.cpp"
#include "board.hpp"

using namespace std;

void print_grid(std::array<std::array<int, 4>, 4> curr_board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << curr_board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // state_queue<int, 5> *sq;
    // sq = new state_queue<int, 5>(10);
    // cout << sq->get_state() << endl;
    // delete(sq);
    // std::array<std::array<int, 4>, 4> curr_board;
    board b1;
    print_grid(b1.get_curr_board());
    cout << "************\n";
    b1.move_right();
    print_grid(b1.get_curr_board());
    cout << "************\n";
    b1.move_right();
    print_grid(b1.get_curr_board());
    cout << "************\n";
    b1.move_right();
    print_grid(b1.get_curr_board());
    // cout << "************\n";
    // b1.move_left();
    // print_grid(b1.get_curr_board());
    // cout << "************\n";
    // b1.move_left();
    // print_grid(b1.get_curr_board());
    // cout << b1.undo() << endl;
    // print_grid(b1.get_curr_board());
    // cout << b1.undo() << endl;
    // print_grid(b1.get_curr_board());
    // cout << b1.redo() << endl;
    // print_grid(b1.get_curr_board());
    // cout << b1.grid.get_state() << endl;
}
