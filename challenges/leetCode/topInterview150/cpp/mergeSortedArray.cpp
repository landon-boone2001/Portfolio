// 88. Merge Sorted Array
// Merges two arrays into one singular, sorted array
// 12/19/23
#include <iostream>
#include <vector>
using namespace std;

// Challenge: write merge()
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int k = 0;
        if (m == 0) {
            for (int i = 0; i < nums2.size(); i++) {
                nums1.at(i) = nums2.at(i);
            }
        }
        // merges values into nums1 list unsorted
        else {
            if (n !=0) {
                for (int i = m; i < nums1.size(); i++) {
                    nums1.at(i) = nums2.at(k);
                    k++;
                }
                // sorts nums1
                for (int i = 0; i < nums1.size(); i++) {
                        for (int j = i; j < nums1.size(); j++) {
                            if (nums1.at(i) > nums1.at(j) ) {
                                int temp;
                                temp = nums1.at(i);
                                nums1.at(i) = nums1.at(j);
                                nums1.at(j) = temp;
                            }
                        }
                }
            }
        }
    }
};
// Test Driver Code
int main () {
    Solution sol;
    vector<int> test1 = {1,5,4};
    vector<int> test2 = {};
    sol.merge(test1, 3,test2, 0);
    for (int i = 0; i < test1.size(); i++) cout << test1.at(i);
}