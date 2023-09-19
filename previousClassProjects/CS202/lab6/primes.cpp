// primes.cpp
// primes.cpp will take a command line argument of an integer value. The program will then output all the primes found between 1 and the value.
// Landon Boone - CS 202
// 10-18-22
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void findPrimes (int size) {
    vector<int> primeList;
    int PrimeCheck;
    double rooti;
    primeList.push_back(2);
    for (int i = 2; i < size+1; i++) {
        PrimeCheck = 0;
        rooti = sqrt(i);
        for (int j = 1; j < rooti+1; j++) {
            if (i % j == 0){
                PrimeCheck++;
            }
        }
        if (PrimeCheck < 2){
            primeList.push_back(i);
        }
    }

    for (int i = 0; i  < primeList.size(); i++ ) {
        if ( i < primeList.size()-1) {
            cout << primeList.at(i) << ", ";
        }
        else {
            cout << primeList.at(i);
        }
    }
}

int main(int argc, char **argv) {
    int size = atoi(argv[1]);
    findPrimes(size);
    return 0;
}