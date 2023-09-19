using namespace std;
#include <iostream>

int main() {
    int median;
    bool swapped;
    int j,k;
    int size;
    int minVal;
    int avg = 0, numsize = 0;

    int temp;
    cout << "enter num of vals: ";
    cin >> size;
    int array[size];
    for (int i =0; i < size; i++) {
        cin >> array[i];
    }
        for (int i =0; i < size; i++) {
         cout << array[i] << " " ;
    }
        cout << " " << endl;

    for (int i = 0; i < size; i++) {
        for (int i=0; i < size-1; i++) {
            swapped = false;
            j = i;
            minVal = array[i] ;
            temp = array[i] ;
            for (j; j < size ; j++ ) {
                if (minVal >= array[j]) {
                    minVal = array[j] ;
                    k = j ;
                    swapped = true;
                }
                array[i] = minVal ;
            }
            if (swapped == true) {
                array[k] = temp;
            }
        }
    }


    for (int i = 0; i < size; i++) {
        cout << array[i] << endl;
    }



    if (size % 2 == 1 ){
        median = array[size/2] + array[size/2 + 1];
        median = median / 2;
    }
    else {
        median = array[size/2];
    }
    cout << "Median: " << median << endl ;

    return 0;
}