
#include <utility>
#include <vector>

#include "result_check/result_check.h"

class Solution {
private:
  using Side = enum {
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
  };

  std::pair<int, int> GetNextIdx(int x, int y, Side side, int start, int size) {
    std::pair<int, int> result;
    switch (side) {
    case UP:
      result.first = start + size - 1;
      result.second = y + (x - start);
      break;
    case RIGHT:
      result.second = start + size - 1;
      result.first = x - (y - start);
      break;
    case DOWN:
      result.first = start;
      result.second = y - (start + size - x - 1);
      break;
    case LEFT:
      result.second = start;
      result.first = x + (start + size - y - 1);
      break;
    }
    return result;
  }

public:
  void Rotate(std::vector<std::vector<int>> &matrix) {
    std::vector<Side> sides = {UP, RIGHT, DOWN, LEFT};
    for (int i = 0; i < matrix.size() / 2; ++i) {
      for (int j = i; j < matrix.size() - i - 1; ++j) {
        std::pair<int, int> curr = {j, i};
        int curr_val = matrix[i][j];
        for (Side s : sides) {
          std::pair<int, int> next =
              GetNextIdx(curr.first, curr.second, s, i, matrix.size() - 2 * i);
          int next_val = matrix[next.second][next.first];
          matrix[next.second][next.first] = curr_val;
          curr = next;
          curr_val = next_val;
        }
      }
    }
  }
};

int main(int, char **) {
  const std::vector<std::vector<std::vector<int>>> cases = {
      {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
      {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}},
  };

  const std::vector<std::vector<std::vector<int>>> expects = {
      {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}},
      {{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    auto cs_copy = cs;
    solution.Rotate(cs_copy);
    CheckResult(cs, expects[i], cs_copy);
  }
  return 0;
}