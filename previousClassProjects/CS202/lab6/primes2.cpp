// primes2.cpp / report.txt
// while reading in integer inputs, the program will determine if the inputted value is a prime number or not, and create a list of all prime values
// between 1 and the value. if the next value inputted is less than the previous inputted value, the program will search
// the previously created list to see if the value is prime or not
// report.txt reports the time primes2 takes to run in varying scenarios, and reports the load factor of a size of 2,000,000 
// Landon Boone - CS 202
// 10-18-22


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> findPrimes (int size, vector<int> primeList) {
    primeList.resize(0);
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

    if (primeList.at(primeList.size()-1) == size){
        cout << "prime" << endl;
    }
    else {
        cout << "not prime" << endl;
    }
    return primeList;
}

void isPrime(int input,  vector<int> primeList) {
    if (find(primeList.begin(), primeList.end(), input) != primeList.end()) {
        cout << "prime" << endl;
    }
    else {
        cout << "not prime" << endl;
    }
}

int main() {
    vector<int> primeList;
    int oldSize = 0;
    int input = 0;
    while (cin >> input) {
        if (input > oldSize) {
            primeList =  findPrimes(input, primeList);
            oldSize = input;
        }
        else {
            isPrime(input, primeList);
        }
    }
    return 0;
}