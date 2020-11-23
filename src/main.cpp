#include <iostream>
#include <vector>

#include "state_queue.hpp"
#include "state_queue.cpp"
#include "board.hpp"

using namespace std;

int main() {
    state_queue<int, 5> sq(10);
    cout << sq.get_state() << endl;

    board b;

    array<array<int, 4>, 4> temp = b.get_curr_board();

    for (auto i : temp) {
        for (auto j : i) {
            cout << j << "\t";
        }
        cout << endl;
    }

    b.move_left();
    cout << endl;

    temp = b.get_curr_board();

    for (auto i : temp) {
        for (auto j : i) {
            cout << j << "\t";
        }
        cout << endl;
    }
}
