// 27. Remove Element
// Removes element from an array based on a given value according to challenge perameters
// by setting the element to a large number, sort the array in ascending order,
// then printing the array's first "k" integers
// 12/20/23
#include <iostream>
#include <vector>
using namespace std;
// Challenge : Remove element from an array matching "val" value
// sets "removed" value to 9999999, then sorts the array in ascending order.
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int counter = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) == val) nums.at(i) = 9999999;
            else counter++;
        }
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j < nums.size(); j++) {
                if (nums.at(i) > nums.at(j) ) {
                    int temp;
                    temp = nums.at(i);
                    nums.at(i) = nums.at(j);
                    nums.at(j) = temp;
                }
            }
        }
        return counter;    
    }
};
int main () {
    Solution sol;
    vector<int> test1 = {1,5,4};
    int loopSize = sol.removeElement(test1, 5);
    for (int i = 0; i < loopSize; i++) cout << test1.at(i);
}