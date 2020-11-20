#include <iostream>
#include <vector>

#include "state_queue.hpp"
#include "state_queue.cpp"

using namespace std;

int main() {
    state_queue<int, 5> sq(10);
    cout << sq.get_state() << endl;
}
