class Solution(object):
    def __init__(self):
        self.outputs = []
        self.curr_stack = []

    def OneSum(self, candidates, target, previous_sum):
        if not candidates:
            return

        curr_count = 0
        curr_sum = 0
        curr_length = len(self.curr_stack)
        while True:
            if curr_count > 0:
                self.curr_stack.append(candidates[0])
            curr_sum = previous_sum + candidates[0] * curr_count
            if curr_sum >= target:
                if curr_sum == target and curr_count > 0:
                    self.outputs.append(list(self.curr_stack))
                break
            self.OneSum(candidates[1:], target, curr_sum)
            curr_count += 1
        del self.curr_stack[curr_length:]

    def CombinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        self.OneSum(candidates, target, 0)
        return list(self.outputs)


def CheckResult(case, expect, result):
    print('Case:', case)
    if sorted(expect) == sorted(result):
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    (
        [2, 3, 6, 7],  # candidates
        7,  # target
    ),
    (
        [2, 3, 5],  # candidates
        8,  # target
    ),
    (
        [2],  # candidates
        1,  # target
    ),
]

EXPECTS = [
    [
        [2, 2, 3],
        [7],
    ],
    [
        [2, 2, 2, 2],
        [2, 3, 3],
        [3, 5],
    ],
    [],
]

for i, (candidates, target) in enumerate(CASES):
    result = Solution().CombinationSum(candidates, target)
    CheckResult((candidates, target), EXPECTS[i], result)
