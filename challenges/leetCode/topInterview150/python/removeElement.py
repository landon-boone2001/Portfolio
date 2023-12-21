# 27. Remove Element
# Removes specified element from list
# 12/21/23
class Solution(object):
    def removeElement(self, nums, val):
        for i in range(nums.count(val)):
            nums.remove(val)