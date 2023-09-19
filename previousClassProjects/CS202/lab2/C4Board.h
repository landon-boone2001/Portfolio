#include <iostream>
#include "C4Col.h"

class C4Board{
    private:
        int numCols;
        C4Col *board;
    public:
        C4Board();
        void display();
        void play();
        int winCheck();
};