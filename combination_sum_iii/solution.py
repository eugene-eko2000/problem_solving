import copy

class Solution(object):
    def CombinationSum3(self, k, n):
        '''
        :type k: int
        :type n: int
        :rtype: List[List[int]]
        '''
        N = 9
        if N < k:
            return []
        curr_k = []
        for i in range(k):
            curr_k.append(i + 1)

        result = []
        finished = False
        full_shift = False
        while not finished:
            s = sum(curr_k)
            if s == n:
                result.append(copy.copy(curr_k))
            if full_shift and s >= n:
                finished = True
                continue

            full_shift = False

            k_idx = k - 1
            while k_idx >= 0:
                if curr_k[k_idx] >= N - (k - k_idx - 1):
                    if k_idx == 0:
                        finished = True
                        break
                else:
                    curr_k[k_idx] += 1
                    for i in range(k_idx + 1, k):
                        curr_k[i] = curr_k[i - 1] + 1
                    if k_idx == 0:
                        full_shift = True
                    break
                k_idx -= 1

        return result


def CheckResult(case, expect, result):
    print('Case:', case)
    if sorted(expect) == sorted(result):
        print('Expected:', expect, 'Test PASSED.')
    else:
        print('Expected:', expect, 'result:', result, 'test FAILED!')


CASES = [
    (3, 7),
    (3, 9),
    (4, 1),
]

EXPECTS = [
    [[1, 2, 4]],
    [[1, 2, 6], [1, 3, 5], [2, 3, 4]],
    [],
]

for i, (k, n) in enumerate(CASES):
    result = Solution().CombinationSum3(k, n)
    CheckResult((k, n), EXPECTS[i], result)
