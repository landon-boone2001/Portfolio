// main.cpp / list.cpp 
// This program will take 2 strings of integers at any list and place each digit into a node in a linked list.
// once each of the digits are placed, the program will add the two together, checking for carried values. If the lists are two different sizes,
// the program will resize the smaller list to add them. Once the lists are added, the sum will be printed out
// Landon Boone - CS 202
// 9-27-22


//Used template code provided by Blake Childress and Dr. Scott Emrich
#include "list.h"
#include <iomanip>
#include <cstdio>
#include <iostream>

using namespace std;




//The program will take the digits from each corresponding node and sum them. If the value is 10 or over, the higher digit will be carried
// over to the next place. If the highest place has a carried sum, a new node will be created for the new digit.
List * sumLists(List * list1, List * list2) {
    int k;
    bool carry = false;
    int spacing;
    List * sum = new List();
    int getDigit;
    if (list1->getCount() == list2->getCount()) {
        int  toSum [list1->getCount()+1];
        k = list1->getCount();
        for (int i = list1->getCount(); i > 0; i--) {
            if (carry){
                getDigit = list1->getDigit(i-1)+list2->getDigit(i-1)+1;
                carry = false;
            }
            else {
                getDigit = list1->getDigit(i-1)+list2->getDigit(i-1);
            }
            if (getDigit > 9){
                carry = true;
                getDigit = getDigit % 10;
            }
            toSum[k] = getDigit;
            k--;

        }
        
        if (carry) {
            getDigit = 1;
            toSum[k] = getDigit;
        }
        else {
            toSum[k] = 0;
        }
        if (carry ){
            for(int i =0; i < list1->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
        else {
            for(int i = 1; i < list1->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
    }
    //The program will make a resized list for list1 or list 2, depending on which is smaller.
    else if (list1->getCount() < list2->getCount()){
        List * resizedList1 = new List();
        spacing = list2->getCount() - list1->getCount();
        for (int i = 0; i < spacing; i++) {
            resizedList1->addNode(0);
        }
        for(int i = 0; i < list1->getCount(); i++) {
            resizedList1->addNode(list1->getDigit(i));
        }
        int  toSum [list2->getCount()+1];
        k = list2->getCount();
        for (int i = list2->getCount(); i > 0; i--) {
            if (carry){
                getDigit = list2->getDigit(i-1)+resizedList1->getDigit(i-1)+1;
                carry = false;
            }
            else {
                getDigit = list2->getDigit(i-1)+resizedList1->getDigit(i-1);
            }
            if (getDigit > 9){
                carry = true;
                getDigit = getDigit % 10;
            }
            toSum[k] = getDigit;
            k--;

        }
        
        if (carry) {
            getDigit = 1;
            toSum[k] = getDigit;
        }
        else {
            toSum[k] = 0;
        }
        if (carry ){
            for(int i =0; i < list2->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
        else {
            for(int i = 1; i < list2->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
        resizedList1->~List();
    }
    else if (list1->getCount() > list2->getCount()){
        List * resizedList2 = new List();
        
        spacing = list1->getCount() - list2->getCount();
        for (int i = 0; i < spacing; i++) {
            resizedList2->addNode(0);
        }
        for(int i = 0; i < list2->getCount(); i++) {
            resizedList2->addNode(list2->getDigit(i));
        }
        int  toSum  [list1->getCount()+1];
        k = list1->getCount();
        for (int i = list1->getCount(); i > 0; i--) {
            if (carry){
                getDigit = list1->getDigit(i-1)+resizedList2->getDigit(i-1)+1;
                carry = false;
            }
            else {
                getDigit = list1->getDigit(i-1)+resizedList2->getDigit(i-1);
            }
            if (getDigit > 9){
                carry = true;
                getDigit = getDigit % 10;
            }
            toSum[k] = getDigit;
            k--;
        }
        
        if (carry) {
            getDigit = 1;
            toSum[k] = getDigit;
        }
        else {
            toSum[k] = 0;
        }
        if (carry ){
            for(int i =0; i < list1->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
        else {
            for(int i = 1; i < list1->getCount()+1; i++) {
                sum->addNode(toSum[i]);
            }
        }
        resizedList2->~List();
    }

    return sum;
}

int main() {
    string input1;
    string input2;
    while (cin >> input1 >> input2) {
        List * list1 = new List();
        List * list2 = new List();  
        List * sum = new List();  
        int digit;
        char toDigit;
        for (int i = 0; i < input1.length(); i++) {
            
            toDigit = input1[i];
            digit = toDigit - '0';
            list1->addNode(digit);
        }
        for (int i = 0; i < input2.length(); i++) {
            toDigit = input2[i];
            digit = toDigit - '0';
            list2->addNode(digit);
        }

        
        sum= sumLists( list1, list2);

        sum->print();
        //list1->~List();
        //list2->~List();
        //sum->~List();
        list1->~List();
        list2->~List();
        sum->~List();
    }
	return 0; 
}