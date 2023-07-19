NORTH = (0, 1)
EAST = (1, 0)
SOUTH = (0, -1)
WEST = (-1, 0)


class Solution(object):
    def TurnLeft(self, d):
        if d == NORTH:
            return WEST
        elif d == WEST:
            return SOUTH
        elif d == SOUTH:
            return EAST
        else:
            return NORTH

    def TurnRight(self, d):
        if d == NORTH:
            return EAST
        elif d == EAST:
            return SOUTH
        elif d == SOUTH:
            return WEST
        else:
            return NORTH

    def RobotSim(self, commands, obstacles):
        """
        :type commands: List[int]
        :type obstacles: List[List[int]]
        :rtype: int
        """
        obs = set([(o[0], o[1]) for o in obstacles])
        dist = 0
        curr_pos = [0, 0]
        d = NORTH
        for command in commands:
            if command == -2:
                d = self.TurnLeft(d)
            elif command == -1:
                d = self.TurnRight(d)
            else:
                for i in range(command):
                    new_pos = (curr_pos[0] + d[0], curr_pos[1] + d[1])
                    if new_pos in obs:
                        break
                    curr_pos = list(new_pos)
                    new_dist = curr_pos[0] * curr_pos[0] + curr_pos[1] * curr_pos[1]
                    if new_dist > dist:
                        dist = new_dist
        return dist


def CheckResult(case, expect, result):
    print("Case:", case)
    if expect == result:
        print("Expected:", expect, "Test PASSED.")
    else:
        print("Expected:", expect, "result:", result, "test FAILED!")


CASES = [([4, -1, 3], []), ([4, -1, 4, -2, 4], [[2, 4]]), ([6, -1, -1, 6], [])]

EXPECTS = [
    25,
    65,
    36,
]

for i, (commands, obstacles) in enumerate(CASES):
    result = Solution().RobotSim(commands, obstacles)
    CheckResult((commands, obstacles), EXPECTS[i], result)
