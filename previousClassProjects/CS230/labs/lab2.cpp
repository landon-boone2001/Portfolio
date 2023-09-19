#include <iostream>

using namespace std;
// 4 6 2 3 8
int main () {
    int size;
    int minValIndex;
    int temp;
    bool swapCheck;
    cin >> size;
    int test[size];
    for (int i = 0; i < size; i++) {
        cin >> test[i];
    }
    for (int i = 0; i < size; i++) {
        cout << test[i] << " ";
    }
    cout << " " << endl;


  
    
    
    for (int i = 0; i < size; i++) {
        minValIndex = i;
        swapCheck = false;
        for (int j = i; j < size; j++){
            if (test[j] < test[minValIndex]) {
                minValIndex = j;
                swapCheck = true;
            }
        }
        if (swapCheck==true){
            temp = test[i];
            test[i] = test[minValIndex];
            test[minValIndex] = temp; 
        }
    }
    
    
    
    
    
    for (int i = 0; i < size; i++) {
        cout << test[i] << " ";
    }

}
