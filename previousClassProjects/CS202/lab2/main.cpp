// main.cpp / C4Board.cpp /C4Col.cpp
// This Program will create a game of Connect 4. First, the program will ask for one or two players. Upon receiving an accepted value (IE 1 or 2), the
// program will begin the game by showing a blank board. If the player is playing single-player mode, they will face against an AI opponent. 
// If the player is playing multi-player mode, they will alternate between Player 1 (X) and Player 2 (O). If a player enters a value that is out of
// bounds or a value of a full collumn, an error message will be outputted, and the player will be prompted to try again. Once a win is detected
// horizontally, vertically, or diagonally, a winner will be declared, and the program will close. After each move, the updated board is displayed
// Landon Boone - CS 202
// 8-26-22

#include "C4Board.h"

int main() {
    C4Board c4;   // instantiate an instance of a C4Board object
    c4.play();        // play game!!
}