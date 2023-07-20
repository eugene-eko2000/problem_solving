class UnionFind(object):
    def __init__(self, n):
        self.groups = [0] * n
        self.group_count = [1] * n
        for i in range(n):
            self.groups[i] = i

    def union(self, u, v):
        u_group = self.find(u)
        v_group = self.find(v)
        if u_group == v_group:
            return
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
    def DistanceLimitedPathsExist(self, n, edgeList, queries):
        """
        :type n: int
        :type edgeList: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        edgeList.sort(key=lambda x: x[2])
        s_queries = sorted(
            [(i, p, q, limit) for i, (p, q, limit) in enumerate(queries)],
            key=lambda x: x[3],
        )

        union_find = UnionFind(n)

        i = 0
        result = [False] * len(queries)
        for q_i, p, q, limit in s_queries:
            while i < len(edgeList) and edgeList[i][2] < limit:
                edge = edgeList[i]
                union_find.union(edge[0], edge[1])
                i += 1
            result[q_i] = union_find.find(p) == union_find.find(q)
        return result


def CheckResult(case, expect, result):
    print("Case:", case)
    if expect == result:
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [
    (
        3,
        [[0, 1, 2], [1, 2, 4], [2, 0, 8], [1, 0, 16]],
        [[0, 1, 2], [0, 2, 5]],
    ),
    (
        5,
        [[0, 1, 10], [1, 2, 5], [2, 3, 9], [3, 4, 13]],
        [[0, 4, 14], [1, 4, 13]],
    ),
]
EXPECTS = [
    [False, True],
    [True, False],
]

for i, (n, edgeList, queries) in enumerate(CASES):
    result = Solution().DistanceLimitedPathsExist(n, edgeList, queries)
    CheckResult((n, edgeList, queries), EXPECTS[i], result)
