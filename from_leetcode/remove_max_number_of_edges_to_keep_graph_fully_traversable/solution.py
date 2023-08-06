class UnionFind(object):
    def __init__(self, n):
        self.groups = [0] * n
        self.group_count = [1] * n
        for i in range(n):
            self.groups[i] = i
        self.groups_num = n

    def union(self, u, v):
        u_group = self.find(u)
        v_group = self.find(v)
        if u_group == v_group:
            return False
        u_cnt = self.group_count[u_group]
        v_cnt = self.group_count[v_group]
        if u_cnt >= v_cnt:
            self.groups[v_group] = u_group
            self.group_count[u_group] += v_cnt
            self.group_count[v_group] = 0
        else:
            self.groups[u_group] = v_group
            self.group_count[v_group] += u_cnt
            self.group_count[u_group] = 0
        self.groups_num -= 1
        return True

    def find(self, v):
        root = v
        while self.groups[root] != root:
            root = self.groups[root]

        while root != v:
            next = self.groups[v]
            self.groups[v] = root
            v = next
        return root


class Solution(object):
    def MaxNumEdgesToRemove(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        alice_union = UnionFind(n)
        bob_union = UnionFind(n)

        result = 0
        for both_types in [True, False]:
            for t, u, v in edges:
                if (t != 3 and both_types) or (t == 3 and not both_types):
                    continue
                alice_redundant = bob_redundant = True
                if t == 1 or t == 3:
                    alice_redundant = not alice_union.union(u - 1, v - 1)
                if t == 2 or t == 3:
                    bob_redundant = not bob_union.union(u - 1, v - 1)
                if alice_redundant and bob_redundant:
                    result += 1

        if alice_union.groups_num > 1 or bob_union.groups_num > 1:
            return -1
        return result


def CheckResult(case, expect, result):
    print("Case:", case)
    if expect == result:
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    (4, [[3, 1, 2], [3, 2, 3], [1, 1, 3], [1, 2, 4], [1, 1, 2], [2, 3, 4]]),
    (4, [[3, 1, 2], [3, 2, 3], [1, 1, 4], [2, 1, 4]]),
    (4, [[3, 2, 3], [1, 1, 2], [2, 3, 4]]),
]
EXPECTS = [2, 0, -1]

for i, (n, edges) in enumerate(CASES):
    result = Solution().MaxNumEdgesToRemove(n, edges)
    CheckResult((n, edges), EXPECTS[i], result)
