#include <iostream>
using namespace std;

int main() {
    char test[3] = {'X', 'X', 'X'};
    cout << test[0] << test[1] << test[2] ;
    if (test[0] == test[1] && test[1] == test[2] && test[0] == 'X') {
        cout << "nice";
    }
    else {
        cout << "dumbass" ;
    } 
    
}

/*
  0 1 2 3 4 5 6
0 X X X X X X X
1 X X X X X X X 
2 X X X X X X X 
3 X X X X X X X
4 X X X X X X X
5 X X X X X X X

for (int i = 0; i < 2) {
    for (int j = 0; j < 4) {
        if (board[i][i] == board[i+1][i+1]) && board[i+1][i+1] == board[i+2][i+2] && board[i+2][i+2] == board[i+3][i+3] && board[1][1] == 'X'){

        }
        else if (board[i][i] == board[i+1][i+1]) && board[i+1][i+1] == board[i+2][i+2] && board[i+2][i+2] == board[i+3][i+3] && board[1][1] == 'O') {
            
        }
    }
}

*/