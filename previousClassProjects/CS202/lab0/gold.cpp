
//Landon Boone
//gold.cpp
//8/24/22



#include <iostream>
#include <string>
#include <fstream>
using namespace std; 


int main() {
    string map;
    char position;
    int numGold = 0;
    while (getline (cin, map)) {
        for (int i=0; i < map.size(); i++) {
            position = map[i];
            if (position != '-' && position != '.' && position != ' ') {
                numGold += int(position) - 64;
            }
        }
        if (map.empty()) {
            break;
        }
    }
    cout << numGold << endl; 
    return 0;
}
