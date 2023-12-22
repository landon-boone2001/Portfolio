# 26. Remove Duplicates from Sorted Array
# Removes duplicates from a pre-sorted array
# 12/22/23
class Solution(object):
    def removeDuplicates(self, nums):
        i = 1
        while i < len(nums):
            val1 = nums[i-1]
            val2 = nums[i]
            if (val1 == val2):
                nums.remove(val1)
            else:
                i = i + 1
        