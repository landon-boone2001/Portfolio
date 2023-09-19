#include "C4Col.h"

C4Col::C4Col() {
    numDiscs = 0;
    maxDiscs = 6;
    col = new char[maxDiscs] ;
    for (int i = 0; i < maxDiscs; i++) {
        col[i] = '*';
    }
};

int C4Col::isFull() {
    if (numDiscs == maxDiscs) {
        return 1;
    }
    else {
        return 0;
    }
}

char C4Col::getDisc(int input){
    return col[input];
}

void C4Col::addDisc(char disc){
    numDiscs = 0;
    for (int i = 0; i < maxDiscs; i++) {
        if (getDisc(i) != '*') {
            numDiscs++;
        }
    }

    if (isFull() == 1){
        std::cout << "Error: Collumn is full, please try again." << std::endl;
    }

    else {
        col[numDiscs] = disc;
    }
} 

int C4Col::getMaxDisc() {
    return maxDiscs;
}