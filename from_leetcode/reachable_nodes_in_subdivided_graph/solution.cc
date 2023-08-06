#include <queue>
#include <string>
#include <tuple>
#include <vector>

#include "result_check/result_check.h"

class Solution {

public:
  int ReachableNodes(const std::vector<std::vector<int>> &edges, int maxMoves,
                     int n) {
    // Initializing a graph matrix.
    std::vector<std::vector<int>> graph(n);
    for (auto &g : graph) {
      g.resize(n, -1);
    }
    for (const auto &edge : edges) {
      graph[edge[0]][edge[1]] = edge[2];
      graph[edge[1]][edge[0]] = edge[2];
    }
    // Initializing distances vector.
    std::vector<int> distances(n, INT_MAX);
    distances[0] = 0;

    // Initializing priority queue for Dijkstra implementation.
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    pq.push(std::make_pair(0, 0));

    // Dijkstra implementation.
    // Allows to reach out as many vertices as possible
    // with a given maxMoves restriction.
    for (; !pq.empty();) {
      auto vertex = pq.top();
      pq.pop();
      for (int j = 0; j < n; ++j) {
        if (graph[vertex.second][j] == -1)
          continue;
        int new_dist = vertex.first + graph[vertex.second][j] + 1;
        if (distances[j] > new_dist) {
          distances[j] = new_dist;
          pq.push(std::make_pair(distances[j], j));
        }
      }
    }

    // Computing reachable vertices.
    int result = 0;
    for (int i = 0; i < n; ++i) {
      // First counting all reachable original vertices.
      if (distances[i] <= maxMoves) {
        ++result;
      }
      // Traverse graph edges.
      for (int j = i + 1; j < n; ++j) {
        if (graph[i][j] == -1) {
          continue;
        }
        // Compute a number of subdivide vertices that can be
        // reached from both original vertices on the edge.
        int this_dist = 0;
        if (distances[i] < maxMoves) {
          this_dist += (maxMoves - distances[i]);
        }
        if (distances[j] < maxMoves) {
          this_dist += (maxMoves - distances[j]);
        }
        // If reachable vertices are overlapped then all subdivide
        // vertices are reachable.
        if (this_dist > graph[i][j]) {
          this_dist = graph[i][j];
        }
        result += this_dist;
      }
    }

    return result;
  }
};

using TestCase = std::tuple<std::vector<std::vector<int>>, int, int>;

int main() {
  const std::vector<TestCase> cases = {
      std::make_tuple(
          std::vector<std::vector<int>>({{0, 1, 10}, {0, 2, 1}, {1, 2, 2}}), 6,
          3),
      std::make_tuple(std::vector<std::vector<int>>(
                          {{0, 1, 4}, {1, 2, 6}, {0, 2, 8}, {1, 3, 1}}),
                      10, 4),
      std::make_tuple(
          std::vector<std::vector<int>>(
              {{1, 2, 4}, {1, 4, 5}, {1, 3, 1}, {2, 3, 4}, {3, 4, 5}}),
          17, 5),
  };

  const std::vector<int> expects = {
      13,
      23,
      1,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    int result = solution.ReachableNodes(std::get<0>(cs), std::get<1>(cs),
                                         std::get<2>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}