// toecheck.cpp
// This program will read in an initial integer value via standard input, and create a tic-tac-toe board with the dimensions of the inputted integer.
// Then, the program will read in values 'X', 'O', and '-', populating the board with these characters. Once the board is populated, the board will
// check diagonally, vertically, and horizontally to see if a victory has been achieved by either party. If the board has been filled and there
// are no remaining empty cells, a Tie will be declared. 
// Landon Boone - CS 202
// 8-30-22

#include <iostream>

using namespace std; 

int main() {

    int boardSize;
    cin >> boardSize;
    char board[boardSize][boardSize];
    int emptyCellCount;
    int winRowCountX, winRowCountO, winColCountX, winColCountO, winDiagCountO, winDiagCountX, winRevCountO, winRevCountX; 
    int k; 

    // The below loop populates the board with the inputted characters

    for (int i = 0; i < boardSize ; i++) {
        for (int j = 0; j < boardSize; j++) {
            cin >> board[i][j];
        }
    }


    // the Below for loop will loop through each row and collumn to check if a player has reached a victory vertically or horizontally.
    for (int i = 0; i < boardSize; i++) {
        winRowCountO = 0;
        winRowCountX = 0;
        winColCountO = 0;
        winColCountX = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'O') {
                winRowCountO++;
            }
            else if (board[i][j] == 'X') {
                winRowCountX++;
            }
            if (board[j][i] == 'O') {
                winColCountO++;
            }
            else if (board[j][i] == 'X') {
                winColCountX++;
            }                         
        }
            
        if (winRowCountO == boardSize || winColCountO == boardSize) {
            cout << "O wins" << endl;
            return 0;
        }
        else if (winRowCountX == boardSize || winColCountX == boardSize) {
            cout << "X wins" << endl; 
            return 0;
        }
    }

        // the below for loop will check the board to see if a player won diagonally;
    for (int i = 0; i < boardSize; i++) {
        k = boardSize-1;
        winDiagCountO = 0;
        winDiagCountX = 0;
        winRevCountO = 0;
        winRevCountX = 0;
        for (int j = 0; j < boardSize; j++ ) {
            if (board[j][j] == 'O') {
                winDiagCountO++;
            }
            else if (board[j][j] == 'X') {
                winDiagCountX++;
            }
            if (board[j][k] == 'O') {
                winRevCountO++;
            }
            else if(board[j][k] == 'X') {
                winRevCountX++;
            }
            k--;
        }
        
        if (winDiagCountO == boardSize) {
            cout << "O wins" << endl;
            return 0;
        }
        else if (winDiagCountX == boardSize) {
            cout << "X wins" << endl;
            return 0;
        }
        if (winRevCountO == boardSize) {
            cout << "O wins" << endl;
            return 0;
        }
        else if (winRevCountX == boardSize) {
            cout << "X wins" << endl;
            return 0;
        }
    }
    // The for loop below will check the board to see if a tie was reached by checking to see if there are any "empty" cells remaining.
    emptyCellCount = boardSize*boardSize;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] != '-') {
                emptyCellCount--;
            }
        }
    }
    
    if (emptyCellCount == 0) {
        cout << "Tie" << endl;
        return 0;
    }
        
}