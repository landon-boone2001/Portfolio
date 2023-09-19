
#include <iostream>

class C4Col{
    private:
        int numDiscs;
        int maxDiscs;
        char *col;
    public:
        C4Col(); 
        int isFull();
        char getDisc(int);
        void addDisc(char);
        int getMaxDisc();


};
