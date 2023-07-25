import asyncio

class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution(object):
    def ReverseOddLevels(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        qu = [root]
        level = 0
        while qu:
            i = 0
            j = len(qu) - 1
            while i <= j:
                tl = qu[i].left
                tr = qu[i].right
                if level % 2:
                    qu[i].left = qu[j].left
                    qu[i].right = qu[j].right
                    qu[j].left = tl
                    qu[j].right = tr
                else:
                    qu[i].left = qu[j].right
                    qu[i].right = qu[j].left
                    qu[j].left = tr
                    qu[j].right = tl
                i += 1
                j -= 1
            new_qu = []
            for el in qu:
                if el.left:
                    new_qu.append(el.left)
                if el.right:
                    new_qu.append(el.right)
            qu = new_qu
            level += 1
        return root


def CheckResult(case, expect, result):
    print("Case:", case)
    if expect == result:
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


def MakeTree(nodes, root, left, right):
    if root >= len(nodes):
        return None
    return TreeNode(
        nodes[root],
        MakeTree(nodes, left, left * 2 + 1, left * 2 + 2),
        MakeTree(nodes, right, right * 2 + 1, right * 2 + 2),
    )

def TreeToList(root_node):
    res = []
    qu = asyncio.Queue()
    qu.put_nowait(root_node)
    while not qu.empty():
        r = qu.get_nowait()
        res.append(r.val)
        if r.left:
            qu.put_nowait(r.left)
        if r.right:
            qu.put_nowait(r.right)
    return res


CASES = [
    [2, 3, 5, 8, 13, 21, 34],
    [7, 13, 11],
    [0, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2],
]

EXPECTS = [
    [2, 5, 3, 8, 13, 21, 34],
    [7, 11, 13],
    [0, 2, 1, 0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1],
]

for i, nodes in enumerate(CASES):
    print(TreeToList(MakeTree(nodes, 0, 1, 2)))
    result = Solution().ReverseOddLevels(MakeTree(nodes, 0, 1, 2))
    CheckResult(nodes, EXPECTS[i], TreeToList(result))
