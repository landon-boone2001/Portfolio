// 1422. Maximum Score After Splitting a String
// splits a string into two substrings, and finds a score
// in which the left substring counts 0's and the right counts 1's
// Loops through all possible substrings in order to find maximum score
// 12/22/23
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int maxScore(string s) {
        int curScore = 0;
        int prevMax = 0;
        string lSub, rSub;
        for (int i = 1; i < s.length(); i++) {
            int curScore = 0;
            lSub = s.substr(0,i);
            rSub = s.substr(i, s.length());
            for (int j = 0; j < lSub.length(); j++) {
                if (lSub[j] == '0') curScore++;
            }
            for (int j = 0; j < rSub.length(); j++) {
                if (rSub[j] == '1') curScore++;
            }
            if (curScore > prevMax) prevMax = curScore;
        }
        return prevMax;
    }
};

int main() {
    string bString = "011101";
    Solution sol;
    cout << sol.maxScore(bString);
}