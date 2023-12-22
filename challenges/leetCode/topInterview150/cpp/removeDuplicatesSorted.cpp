// 26. Remove Duplicates from Sorted Array
// removes duplicate values from an array by replacing the duplicate
// values with a large int and sorting in ascending order,
// then printing the first k integers, where k is the number of unique elements
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int counter = 1;
            for (int i = 1; i < nums.size(); i++) {
                if (nums.at(i) == nums.at(i-1)) nums.at(i-1) = 9999999;
                else counter++;
            }
            int  temp, j;
            for (int i = 1; i < nums.size(); i++) {
                temp = nums.at(i);
                j = i - 1;
                while (j >= 0 && nums.at(j) > temp) {
                    nums.at(j + 1) = nums.at(j);
                    j = j - 1;
                }
                nums.at(j + 1) = temp;
            }
                    return counter;
        }
};


int main() {
    Solution sol;
    vector<int> test1 = {1,2,2,3,4,4};
    int loopSize = sol.removeDuplicates(test1);
    for (int i = 0; i < loopSize; i++) cout << test1.at(i);
    return 0;
}