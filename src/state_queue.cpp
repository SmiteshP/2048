#include "state_queue.hpp"

template <typename T, int size>
state_queue<T, size>::state_queue(T elem)
	: curr_state(elem) {
}

template <typename T, int size>
state_queue<T, size>::~state_queue() = default;

template <typename T, int size>
void state_queue<T, size>::push(T elem) {
	if (redo_space.size() != 0) {
		redo_space.clear();
	}
	undo_space.push_back(curr_state);
	curr_state = elem;
	if (undo_space.size() == size) {
		undo_space.pop_front();
	}
}

template <typename T, int size>
bool state_queue<T, size>::can_redo() const {
	return !redo_space.empty();
}

template <typename T, int size>
void state_queue<T, size>::redo() {
	assert(!redo_space.empty());
	undo_space.push_back(curr_state);
	curr_state = redo_space.top();
	redo_space.pop();
}

template <typename T, int size>
bool state_queue<T, size>::can_undo() const {
	return !undo_space.empty();
}

template <typename T, int size>
void state_queue<T, size>::undo() {
	assert(!undo_space.empty());
	redo_space.push(curr_state);
	curr_state = undo_space.back();
	undo_space.pop_back();
}

template <typename T, int size>
T state_queue<T, size>::get_state() const {
	return curr_state;
}
