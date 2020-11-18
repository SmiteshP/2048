#include <iostream>
#include <vector>

// #include "state_queue.hpp"
// #include "state_queue.cpp"
#include "board.hpp"

using namespace std;

int main()
{
	// state_queue<int, 5> sq(10);
	// cout << sq.get_state() << endl;

	board b1;
	b1.print_grid();

	cout << b1.undo() << endl;
	cout << b1.undo() << endl;
	cout << b1.redo() << endl;
	// cout << b1.grid.get_state() << endl;
}
