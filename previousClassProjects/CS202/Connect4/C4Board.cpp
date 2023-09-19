#include "C4Board.h"
#include <iostream>
C4Board::C4Board() {
    numCols = 7;
    board = new C4Col[numCols];
};

void C4Board::play() {
    bool running = true;
    int turnCounter = 0;
    char playerMove;
    int playerCount;
    int colInput;
    int winCheck = 0;
    // Takes a player count of 1 or 2. If 1 is entered, the Connect 4 game enters single-player mode, playing against an AI opponent. 
    // If 2 is entered, the game enters multi-player mode. Any other integer input will return an error message, and ask for the user to 
    // enter another playercount.
    do {
        std::cout << "Enter Player Count (Maximum of 2 Players): ";
        std::cin >> playerCount;
        if (playerCount > 2 || playerCount < 1){
            std::cout << "Error: Player Count out of bounds. Please enter 1 for single player and 2 for multiplayer." << std::endl;
        }
        else {
            running = false;
        }
    } while (running);

    while (winCheck == 0){
        // Singleplayer Block
        // Player X will submit a move, then the AI player will automatically make a move.
        if (playerCount == 1) {

            if (turnCounter % 2 != 0) {
                playerMove = 'O' ;
            }
        
            else if (turnCounter % 2 == 0){ 
                playerMove = 'X';
            }

            display();
            std::cout << "Enter a Column to place a disc into: ";
            if (playerMove == 'X') {
                std::cin >> colInput;                
            }
            else if (playerMove == 'O'){
                colInput = rand() % 6;
            }
            if (colInput < 0 || colInput > 6) {
                std::cout << "Error: attempted move out of bounds. Please try again." << std::endl;
            }
           
            else {            
                board[colInput].addDisc(playerMove);
                turnCounter++;
            }

            winCheck = C4Board::winCheck();            
        }
        // Multiplayer Block
        // Player X will submit a move, then Player O will submit a move.
        if (playerCount == 2) {
            
            if (turnCounter % 2 != 0) {
                playerMove = 'O' ;
            }
        
            else if (turnCounter % 2 == 0){ 
                playerMove = 'X';
            }

            display();
            std::cout << "Enter a Column to place a disc into: ";
            std::cin >> colInput;
           
            if (colInput < 0 || colInput > 6) {
                std::cout << "Error: attempted move out of bounds. Please try again." << std::endl;
            }
           
            else {            
                board[colInput].addDisc(playerMove);
                turnCounter++;
            }

            winCheck = C4Board::winCheck();
        }
    }
}
/*Creates a visual display of the current board. The first for loop prints out the "coordinates" of each collumn */
void C4Board::display() {
    
    for (int k = 0; k < numCols; k++) {
        std::cout << "  " << k << " ";
    }
   
    std::cout << " " << std::endl;
    for (int i = board->getMaxDisc()-1; i >= 0; i--) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "| " << board[j].C4Col::getDisc(i) << " " ; 
        }
        std::cout << "|" << std::endl;
    }
}
/*Checks after each move to see if a player has won diagonally, horizontally, or vertically. If a player wins, the winning board will be displayed 
and the program will output "X Wins" or "O Wins" before returning winCheck, an int that determines if the game is over, or if the game continues. */
int C4Board::winCheck() {
    int HorWinO, HorWinX, VertWinO, VertWinX;
    int winCheck = 0;
        /* Checks the board diagonally for a win. The below if statements for the diagonal checks will determine if all the 
        characters in a diagonal are the same, then determine if they are an X or an O. Once this is determined, a winner is declared.*/
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[j].C4Col::getDisc(i) == board[j+1].C4Col::getDisc(i+1) && board[j+1].C4Col::getDisc(i+1) == board[j+2].C4Col::getDisc(i+2) && board[j+2].C4Col::getDisc(i+2) == board[j+3].C4Col::getDisc(i+3) && board[j].C4Col::getDisc(i) == 'X' ){
                    display();                        
                    std::cout << "X Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
                
                if (board[j].C4Col::getDisc(i) == board[j+1].C4Col::getDisc(i+1) && board[j+1].C4Col::getDisc(i+1) == board[j+2].C4Col::getDisc(i+2) && board[j+2].C4Col::getDisc(i+2) == board[j+3].C4Col::getDisc(i+3) && board[j].C4Col::getDisc(i) == 'O' ){
                    display();
                    std::cout << "O Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
                
                if (board[j].C4Col::getDisc(i+3) == board[j+1].C4Col::getDisc(i+2) && board[j+1].C4Col::getDisc(i+2) == board[j+2].C4Col::getDisc(i+1) && board[j+2].C4Col::getDisc(i+1) == board[j+3].C4Col::getDisc(i) && board[j].C4Col::getDisc(i+3) == 'X' ){
                    display();
                    std::cout << "X Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
                
                if (board[j].C4Col::getDisc(i+3) == board[j+1].C4Col::getDisc(i+2) && board[j+1].C4Col::getDisc(i+2) == board[j+2].C4Col::getDisc(i+1) && board[j+2].C4Col::getDisc(i+1) == board[j+3].C4Col::getDisc(i) && board[j].C4Col::getDisc(i+3) ==  'O' ){
                    display();
                    std::cout << "O Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
            }
        }            
        /* Checks the board for a horizontal and vertical victory by comparing 4 characters in a row. If an X or an O appears, the 
        count of the winX or winO will increase by one with respect to the sequence being horizontal or vertical. If a single character differs, the winX/winO
        will reset to 0. Once one of these values reaches 4, a winner is declared  */
        for (int i = board->getMaxDisc()-1; i >= 0; i--) {
            VertWinO = 0; 
            VertWinX = 0;
            HorWinO = 0; 
            HorWinX = 0;
            for (int j = 0; j < numCols; j++) {
                if (board[j].C4Col::getDisc(i) == 'X') {
                    HorWinO = 0;
                    HorWinX++;    
                }
               
                else if (board[j].C4Col::getDisc(i) == 'O') {
                    HorWinX = 0;
                    HorWinO++;
                }
               
                else {
                    HorWinO = 0;
                    HorWinX = 0;
                }
               
                if (board[i].C4Col::getDisc(j) == 'X') {
                    VertWinO = 0;
                    VertWinX++;    
                }
               
                else if (board[i].C4Col::getDisc(j) == 'O') {
                    VertWinX = 0;
                    VertWinO++;
                }
               
                else {
                    VertWinO = 0;
                    VertWinX = 0;
                }


                if (HorWinO == 4) {
                    display();
                    std::cout << "O Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
    
                else if (HorWinX == 4) {
                    display();
                    std::cout << "X Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
                
                if (VertWinO == 4) {
                    display();
                    std::cout << "O Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
    
                else if (VertWinX == 4) {
                    display();
                    std::cout << "X Wins" << std::endl;
                    winCheck = 1;
                    break;
                }
            }
        }  
    return winCheck;
}