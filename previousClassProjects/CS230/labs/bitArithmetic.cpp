// bitArithmetic.cpp
// This program will ask for an integer input 1,2, or 3 corresponding to an operation: Addition, Subtraction, and Two's Complement.
// If the integer input is not one of these, the program will print an error message and return an error code 1.
// otherwise, the program will ask for a left hand and right hand integer value if the selected operation is Addition or Subtraction.
// if the operation selected is a Two's Complement, only the lefthand value will be taken. Once these inputs are provided, the program will output 
// the resulting value, and exit with error code 0
// 11-14-22
// Landon Boone

#include <iostream>

using namespace std;

/*addition using bitwise operators. Finds the carry Value
via AND, and continues to loop until the carried value is 0
Each iteration, the lefthand value will be updated to be the
XOR of the lefthand and righthand value.
At the end of each iteration, the carried Value is shifted left, and becomes
the new righthand value. Once the righthand value is 0, the resulting lefthand value
is printed*/
long badd(long leftVal, long rightVal) {
    long result;
    int carryVal;
    while (rightVal != 0) {
        carryVal = leftVal & rightVal;
        leftVal = leftVal ^ rightVal;
        rightVal = carryVal << 1;
    }
    result = leftVal;
    return result;
}
/*subtraction using bitwise operators. Finds the carry Value
via AND from the complement of the Left value and the right value, and continues to loop until the carried value is 0
Each iteration, the lefthand value will be updated to be the
XOR of the lefthand and righthand value.
At the end of each iteration, the carried Value is shifted left, and becomes
the new righthand value. Once the righthand value is 0, the resulting lefthand value
is printed*/
long bsub(long leftVal, long rightVal) {
    long result;
    int carryVal, notLeft;
    while (rightVal != 0) {
        notLeft = ~leftVal;
        carryVal = notLeft & rightVal;
        leftVal = leftVal ^ rightVal;
        rightVal = carryVal << 1;
    }
    result = leftVal;
    return result; 
}
/*Two's Complement using bitwise operators. Finds the two's complement
by finding the complement of the entered value, then adding one.*/
long btwos(long leftVal) {
    long result;
    long rightVal = 1;
    leftVal = ~leftVal;
    result = badd(leftVal, rightVal);
    return result;
}

int main() {
    int leftVal, rightVal, result;
    int operation;
    cout << "---- Operation List ----" << endl;
    cout << "1 - Addition" << endl;
    cout << "2 - Subtraction" << endl;
    cout << "3 - Two's Complement" << endl;
    cout << "Enter an Operation Integer: ";
    cin >> operation;
    cout << " " << endl;

    if (operation < 4 && operation > 0) {
        cout << "Enter a left value: " ;
        cin >> leftVal;

        if (operation != 3) {
            cout << "Enter a right value: " ;
            cin >> rightVal;
        }
        if (operation == 1) {
            result = badd(leftVal, rightVal);
        }
        else if (operation == 2) {
            result = bsub(leftVal, rightVal);
        }
        else if (operation == 3) {
            result = btwos(leftVal);
        }
        cout << "Result: " << result;
        cout << " " << endl;
    }
    else {
         cout << "Error: Unknown Operation. Exiting...";
        return 1;
    }
    
    return 0;
}