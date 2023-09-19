// solution.cpp
// solution will take two initial arguments via standard input: N and K, with N being the number of elements to be inputted, and K being the 
// Kth smallest integer to be found. The program will then take N integer inputs, and will determine if the sequence inputted is a max-heap or not
// and will output Y or N respectively. Then, the program will output the Kth smallest integer.
// Landon Boone - CS 202
// 11-22-22

#include <iostream>
#include <vector>

using namespace std;
// checks to see if the initial vector is a max heap or not. Used a source https://www.codesdope.com/blog/article/to-check-if-an-array-represents-min-or-max-heap/#:~:text=Max%2Dheap%20or%20Not&text=And%20to%20verify%20if%20a,than%20its%20children%20or%20not.
// to reinforce knowledge on the check and followed the structure provided.
char maxHeapCheck(vector<int> inputVec, int vecSize) {
    char isMaxHeap;
    isMaxHeap = 'Y';
    for (int i = 0; i < (vecSize-2)/2; i++) {
        if (inputVec.at(2*i+1) > inputVec.at(i) || inputVec.at(2*i+2) > inputVec.at(i)) {
            isMaxHeap = 'N';
            return isMaxHeap;
        }
    }
    return isMaxHeap;
}

// uses the push function provided in Plank's notes in order to create a heap from the inputted vector. I renamed p to "parent" for clarity
void Push(vector <int> &heap, int val)
{
  int i, parent;
  i = heap.size();
  heap.push_back(val);     // Put the value onto the end of the heap.

  while (i > 0) {          // Percolate up, starting at i.
    parent = (i-1) / 2;         // You stop when you reach the root, or when the parent's value
    if (heap[parent] > val) {   
      heap[i] = heap[parent];
      heap[parent] = val;
      i = parent;
    } else {
      return;
    }
  }
}
// Finds the Kth val by removing the minimum value from the tree and remaking the tree using Push() k-2 times before printing the new minimum value
// where k is the the inputted K value.
int findKthVal(vector<int> heap, int k) {
    int kthVal;
    vector<int> tempHeap;
    vector<int> newHeap;
    if (k == 1) {
        kthVal = heap.at(0);
        return kthVal;
    }
    else if (k == 2) {
        kthVal = heap.at(1);
        return kthVal;
    }
    else {
        for (int j = 1; j < heap.size(); j++) {
            Push(tempHeap, heap.at(j));
        }
        for (int z = 0; z < k-2; z++) {
            newHeap.resize(0);
                for (int j = 1; j < tempHeap.size(); j++) {
                Push(newHeap, tempHeap.at(j));
            }
            tempHeap.resize(0);
            for (int i = 0; i < newHeap.size(); i++) {
                tempHeap.push_back(newHeap.at(i));
            }
        }
        kthVal = newHeap.at(0);
            return kthVal;
        }
}

int main(int argc, char *argv[]) {
    int inputSize;
    while (cin >> inputSize) {
        int kthInt;
        int input;
        vector<int> inputVec;
        vector<int> heapVec;
        cin >> kthInt;
        // stores the inputted values into an initial vector
        for (int i = 0; i < inputSize; i++) {
            cin >> input;
            inputVec.push_back(input);
        }
        // creates a minHeap from the input. stores this initial vector in order to check it later with maxHeapCheck to see if it is initially
        // a max heap.
        for (int i = 0; i < inputSize; i++) {
                Push(heapVec, inputVec[i]);
        }
        
        cout << maxHeapCheck(inputVec,inputSize) << "  " << findKthVal(heapVec, kthInt) << endl;
    }
    return 0;
}