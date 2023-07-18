import copy


class Solution(object):
    def AsComb(self, c, n, k):
        digits = []
        for i in range(n - 1, -1, -1):
            digit = int(c / pow(k, i))
            digits.append(str(digit))
            c = c % pow(k, i)
        return "".join(digits)

    def DFS(self, n, k):
        vertex = 0
        comb_num = pow(k, n)
        output = [self.AsComb(vertex, n, k)[:-1]]
        visited = set()
        while len(visited) < comb_num:
            v_str = self.AsComb(vertex, n, k)
            for last_digit in range(k - 1, -1, -1):
                conn = 0
                if k > 1:
                    conn = int(v_str[1:] + str(last_digit), k)
                if conn in visited:
                    continue
                vertex = conn
                visited.add(vertex)
                output.append(str(last_digit))
                break
        return output

    def CrackSafe(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        output = self.DFS(n, k)
        return "".join(output)


def CheckResult(case, expect, result):
    print("Case:", case)
    if sorted(expect) == sorted(result):
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    (1, 2),
    (2, 2),
]

EXPECTS = [
    "10",
    "01100",
]

for i, (n, k) in enumerate(CASES):
    result = Solution().CrackSafe(n, k)
    CheckResult((n, k), EXPECTS[i], result)
