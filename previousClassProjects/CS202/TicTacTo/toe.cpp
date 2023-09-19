// toe.cpp
// This program will take an integer input to create an empty square grid initially populated by the character ' '. 
// Next, the program will ask player 1,  for a coordinate input of two integers between 1 and the inputted length of the board.
// If the user inputs 1 1, the top left cell will be filled, and if the user inputs the maximum length N N, the bottom right cell will be filled.
// Once provided, the program  will replace the respective cell in the grid with the player's character. Once the player's turn ends, a new grid is
// generated,  demonstrating the last move entered, and will begin to check for a victory or tie before allowing the next player to enter a coordinate.
// If a player enters a coordinate that is out of bounds or a cell already populated by an X or O, the program will prompt the player to enter
// another Coordinate.
// Landon Boone - CS 202
// 8-26-22


#include <iostream> 

using namespace std;


int main() {
    int turnCounter = 1;
    int k;
    bool running = true;
    int setRow, setCol;
    int boardSize;
    cout << "Enter an integer to create a board sized [input] x [input]: " ; 
    cin >> boardSize;
    char board[boardSize][boardSize];
    string input;
    char playerMove;
    bool inputtingMove;
    int emptyCellCount;
    int winRowCountX, winRowCountO, winColCountX, winColCountO, winDiagCountO, winDiagCountX, winRevCountO, winRevCountX; 
    
    //The for loop below initializes each cell as a ' ' character
    for (int row=0; row < boardSize; row++) {
        for (int collumn = 0; collumn < boardSize; collumn++) {
            board[row][collumn] = '-' ;
        }
    }
    
    while (running) {
        inputtingMove = true;
        //At the beginning of each turn, the below for loop prints the board with the most recent move. In the beginning, a blank board will be printed.
        for(int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                cout << " " << board[i][j]; 
            }
            cout << " " << endl;
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
                cout << "O wins" ;
                return 0;
            }
            else if (winRowCountX == boardSize || winColCountX == boardSize) {
                cout << "X wins" ; 
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
                cout << "O wins" ;
                return 0;
            }
            else if (winDiagCountX == boardSize) {
                cout << "X wins" ;
                return 0;
            }
            if (winRevCountO == boardSize) {
                cout << "O wins" ;
                return 0;
            }
            else if (winRevCountX == boardSize) {
                cout << "X wins" ;
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
            cout << "Tie" ;
            return 0;
        }
        

        // the below if/else if statement checks the turn counter to determine if player O
        // or Player X is placing a move on the board. Player O begins the game.
        if (turnCounter % 2 != 0) {
            playerMove = 'O' ;
        }
        else if (turnCounter % 2 == 0){ 
            playerMove = 'X';
        }
        
        cout << "Player " << playerMove << "'s move: " << endl;
        // The below while loop will take a set of coordinates, and depending on which player's turn it is, will mark the spot on the board in their mark.
        // if a Player attempts to make a move outside of the allowed bounds or attempts to overrwrite the other player's move, the player will be prompted to
        // make a new move. The expected input is to be inputted as coordinate 1 1 being the top left cell, and coord N, N being the bottom right cell of the grid.
        while (inputtingMove) {
            cout << "Please input two coordinates between 1 and " << boardSize << ": ";
            cin >>  setRow >> setCol;
            if (setRow > boardSize || setCol > boardSize  || setRow < 1 || setCol < 1) {
                cout << "Error: Attempted Move out of Bounds." << endl;
            }
            else if (board[setRow-1][setCol-1] != '-') {
                cout << "Error: Space Already Occupied; Try again." << endl;
            }
            else {
                inputtingMove = false;
            }
        }
        board[setRow-1][setCol-1] = playerMove;

        turnCounter++;
    }
    
    return 0;
}