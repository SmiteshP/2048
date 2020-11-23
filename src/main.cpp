#include <iostream>
#include <vector>
#include <random>

#include "board.hpp"

using namespace std;

void print_grid(std::array<std::array<int, 4>, 4> curr_board) {
    cout << "---------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if(curr_board[i][j]) cout << curr_board[i][j] << "|";
            else cout << " |";
        }
        cout << "\n---------" << endl;
    }
}

bool Move(board *S, int i){
    if(i==0) {
        cout << "left:\n"; 
        if(S->next_left_possible()){
            S->move_left();
            return true;
        }
        else return false;
    }
    else if(i==1) {
        cout << "up:\n"; 
        if(S->next_up_possible()){
            S->move_up();
            return true;
        }
        else return false;
    }
    else if(i==2) {
        cout << "down:\n"; 
        if(S->next_down_possible()){
            S->move_down();
            return true;
        }
        else return false;
    }
    else if(i==3) {
        cout <<"right:\n"; 
        if(S->next_right_possible()){
            S->move_right();
            return true;
        }
        else return false;
    }
    
    return false;
}

void popl_assignment(){
    board *S = new board();
    print_grid(S->get_curr_board());
    cout << "***************\n";
    cout << "score : " << S->get_curr_sum() << endl;
    cout << "***************\n";

    while(S->get_curr_sum()<8){
        
        int i = rand()%4;
        
        while(!Move(S, i)){
            i = rand()%4;
        }
        
        print_grid(S->get_curr_board());
        cout << "***************\n";
        cout << "score : " << S->get_curr_sum() << endl;
        cout << "***************\n";
        if(S->get_curr_sum()==8) break;
        
        else if(S->get_curr_sum()>8){
            while(S->get_curr_sum()>8){
                S->undo();
                print_grid(S->get_curr_board());
                cout << "***************\n";
                cout << "score : " << S->get_curr_sum() << endl;
                cout << "***************\n";
            }
        }
    }
    delete S;
}

void play_2048(){
    board S;
    while(1){
        print_grid(S.get_curr_board());
        cout << "************\n";
        char c;
        cin >> c;
        cout << "************\n";
        if(c=='a') {
            S.move_left();
        }
        if(c=='s') {
            S.move_down();
        }
        if(c=='d') {
            S.move_right();
        }
        if(c=='w') {
            S.move_up();
        }
        if(c=='u') {
            S.undo();
        }
        if(c=='r') {
            S.redo();
        } 
        if(c=='q') break;
    }
}

int main() {
    
    srand(0);
    
    char c;
    cout << "Enter 'a' to solve assignment and 'p' to play game: ";
    cin >> c;
    cout << "You have chosen " << c << endl;
    if(c=='a') popl_assignment();
    else play_2048();
    
}
