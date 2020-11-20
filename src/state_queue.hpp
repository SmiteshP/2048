#pragma once

#include <deque>
#include <stack>

template <typename T, int size>
class state_queue {
 public:
    // Instantiate with starting element
    state_queue(T elem);
    ~state_queue();

    // Push new element
    void push(T elem);

    // Check if redo is possible and redo
    bool can_redo() const;
    void redo();

    // Check if undo is possible and undo
    bool can_undo() const;
    void undo();

    // Retreive value of curr_state
    T get_state() const;

 private:
    T curr_state;
    std::deque<T> undo_space;
    std::deque<T> redo_space;
};
