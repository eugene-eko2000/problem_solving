#include <algorithm>
#include <queue>
#include <vector>

#include "../result_check/result_check.h"

class Solution {
public:
  std::vector<int>
  FindRedundantConnection(const std::vector<std::vector<int>> &edges) {
    std::vector<std::vector<int>> graph(edges.size());
    for (const auto &edge : edges) {
      graph[edge[0] - 1].push_back(edge[1]);
      graph[edge[1] - 1].push_back(edge[0]);
    }
    for (int i = 0; i < graph.size(); ++i) {
      if (graph[i].size() == 1) {
        // Go through terminator edge and its connections.
        std::vector<int> *curr_node = &graph[i];
        int curr_node_idx = i;
        for (; curr_node->size() == 1;) {
          std::vector<int> *next_node = &graph[(*curr_node)[0] - 1];
          int j = 0;
          for (; (*next_node)[j] != curr_node_idx + 1; ++j) {
          }
          std::swap((*next_node)[j], (*next_node)[next_node->size() - 1]);
          next_node->pop_back(); // if not in the loop then size becomes 1.
          curr_node_idx = (*curr_node)[0] - 1;
          curr_node->pop_back(); // turns into an empty vector.
          curr_node = next_node;
        }
      }
    }
    for (int i = edges.size() - 1; i >= 0; --i) {
      if (graph[edges[i][0] - 1].empty() || graph[edges[i][1] - 1].empty()) {
        // An edge out of loop, cleaned up.
        continue;
      }
      return edges[i];
    }
    return {}; // Should never happen
  }
};

int main(int, char **) {
  const std::vector<std::vector<std::vector<int>>> cases = {
      {{1, 2}, {1, 3}, {2, 3}},
      {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}},
  };

  const std::vector<std::vector<int>> expects = {
      {2, 3},
      {1, 4},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<int> result = solution.FindRedundantConnection(cs);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}