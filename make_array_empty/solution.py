class FenwickTree:
    def __init__(self, capacity):
        self.fwt = [0] * capacity
        self.capacity = len(self.fwt)

    def query(self, idx):
        result = 0
        while idx > 0:
            result += self.fwt[idx]
            idx -= idx & -idx

        return result

    def update(self, idx, val):
        while idx < self.capacity:
            self.fwt[idx] += val
            idx += idx & -idx


class Solution(object):
    def CountOperationsToEmptyArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        result = 0
        sorted_nums = sorted([(num, idx) for idx, num in enumerate(nums)])
        fwt = FenwickTree(len(nums) + 1)
        curr_idx = -1
        for _, idx in sorted_nums:
            left_r = fwt.query(min(curr_idx + 1, idx + 1))
            right_r = fwt.query(max(curr_idx + 1, idx + 1))
            if curr_idx < idx:
                removed = right_r - left_r
                result += idx - curr_idx
            else:
                removed = fwt.query(len(nums)) - right_r + left_r
                result += len(nums) - (curr_idx - idx)
            curr_idx = idx
            result -= removed
            fwt.update(idx + 1, 1)
        return result


def CheckResult(case, expect, result):
    print("Case:", case)
    if expect == result:
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    [3, 4, -1],
    [1, 2, 4, 3],
    [1, 2, 3],
]
EXPECTS = [5, 5, 3]

for i, nums in enumerate(CASES):
    result = Solution().CountOperationsToEmptyArray(nums)
    CheckResult(nums, EXPECTS[i], result)
