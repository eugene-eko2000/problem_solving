import copy


class Solution(object):
    def Combine(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[List[int]]
        """
        if n < k:
            return []
        curr_k = []
        for i in range(k):
            curr_k.append(i + 1)

        result = []
        finished = False
        while not finished:
            result.append(copy.copy(curr_k))

            k_idx = k - 1
            while k_idx >= 0:
                if curr_k[k_idx] >= n - (k - k_idx - 1):
                    if k_idx == 0:
                        finished = True
                        break
                else:
                    curr_k[k_idx] += 1
                    for i in range(k_idx + 1, k):
                        curr_k[i] = curr_k[i - 1] + 1
                    break
                k_idx -= 1

        return result


def CheckResult(expect, result):
    if sorted(expect) == sorted(result):
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    (4, 2),
    (1, 1),
]

EXPECTS = [
    [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]],
    [[1]],
]

for i, (n, k) in enumerate(CASES):
    result = Solution().Combine(n, k)
    CheckResult(EXPECTS[i], result)
