// nqueens.cpp
// This program takes an integer command line input to create a board size N x N. The program will then recursively create
// all potential solutions for a problem outlining where 8 potential queens could be placed upon a board. While creating these potential solutions,
// the program will test them to see if they are true solutions, and if so, will print them.
// Landon Boone - CS 202
// 10-23-22
//Used nQueens example provided by Dr. Emrich in 10/18 class.
#include <iostream>
using namespace std;
//checks if the board is a solution. If valid, the board will be printed
bool ValidCheck (int board[], int size) {
        int diffRow, diffCol;

        //In-depth check for diagonal and horizontal threats for those not weeded out prior
        for (int i = 0; i < size; i++) {
            for (int j = i+1; j < size; j++) {
                if (board[i] == board[j]) {
                    return false;
                }
            }
            
            for (int j = 1; j < size-i; j++) {
                diffRow = board[i+j] - board [i];
                diffCol = j;
                if (diffRow == diffCol || -diffRow == diffCol) {
                    return false;
                }
            }
        }
        
    return true;
}
//recursive function that creates potential solutions for a board of N size and checks the validity of the created solutions.
void nqueens (int board[], int position, int size) {
    bool isValid;
    isValid = ValidCheck(board, size);
    if (size == position) {
        if (isValid){
            for (int i = 0; i < size-1; i++) {
                cout << board[i] << ", ";
            }
            cout << board[size-1] << endl;
        }
    }
    
    else {
        for (int i = 0; i < size; i++) {
            board[position] = i;
            nqueens (board, position+1, size);
        }
    }
}

int main(int argc, char** argv) {
    int size = atoi(argv[1]);
    int board[size];
    nqueens(board, 0, size);
    return 0;
}