#include <queue>
#include <tuple>
#include <vector>

#include "result_check/result_check.h"

inline unsigned long long pack(int x, int y) {
  return (static_cast<unsigned long long>(x) << 20) |
         static_cast<unsigned long long>(y);
}

inline std::pair<int, int> unpack(unsigned long long p) {
  static constexpr unsigned long long mask = 0xfffff;
  return std::make_pair(p >> 20, p & mask);
}

inline int compute_distance(const std::pair<int, int> &v1,
                            const std::pair<int, int> &v2) {
  return abs(v1.first - v2.first) + abs(v1.second - v2.second);
}

class Solution {
private:
public:
  int MinimumCost(const std::vector<int> &start, const std::vector<int> &target,
                  const std::vector<std::vector<int>> &specialRoads) {
    std::priority_queue<std::pair<int, unsigned long long>,
                        std::vector<std::pair<int, unsigned long long>>,
                        std::greater<std::pair<int, unsigned long long>>>
        pq;
    std::unordered_map<unsigned long long, int> dists;

    auto target_v = std::make_pair(target[0], target[1]);
    unsigned long long target_p = pack(target[0], target[1]);
    unsigned long long start_p = pack(start[0], start[1]);
    dists[start_p] = 0;
    pq.push(std::make_pair(0, start_p));
    int min_dist = INT_MAX;
    while (!pq.empty()) {
      int curr_d = pq.top().first;
      auto curr_v = unpack(pq.top().second);
      if (pq.top().second == target_p) {
        return curr_d;
      }
      pq.pop();
      for (const auto &sr : specialRoads) {
        auto sr_start = std::make_pair(sr[0], sr[1]);
        unsigned long long sr_start_p = pack(sr[0], sr[1]);
        auto sr_target = std::make_pair(sr[2], sr[3]);
        unsigned long long sr_target_p = pack(sr[2], sr[3]);
        int sr_dist = sr[4];

        int dist_to_sr_start = compute_distance(sr_start, curr_v);
        int dist_to_sr_target = compute_distance(sr_target, curr_v);
        if (curr_v == sr_start && sr_dist < dist_to_sr_target) {
          dist_to_sr_target = sr_dist;
        }
        if (curr_v != sr_start) {
          auto sr_start_dist_it = dists.find(sr_start_p);
          if (sr_start_dist_it == dists.end() ||
              sr_start_dist_it->second > curr_d + dist_to_sr_start) {
            dists[sr_start_p] = curr_d + dist_to_sr_start;
            pq.push(std::make_pair(curr_d + dist_to_sr_start, sr_start_p));
          }
        }
        if (curr_v != sr_target) {
          auto sr_target_dist_it = dists.find(sr_target_p);
          if (sr_target_dist_it == dists.end() ||
              sr_target_dist_it->second > curr_d + dist_to_sr_target) {
            dists[sr_target_p] = curr_d + dist_to_sr_target;
            pq.push(std::make_pair(curr_d + dist_to_sr_target, sr_target_p));
          }
        }
      }
      int dist_to_target = compute_distance(target_v, curr_v);
      auto target_dist_it = dists.find(target_p);
      if (target_dist_it == dists.end() ||
          target_dist_it->second > curr_d + dist_to_target) {
        dists[target_p] = curr_d + dist_to_target;
        pq.push(std::make_pair(curr_d + dist_to_target, target_p));
      }
    }
    return min_dist;
  }
};

int main(int, char **) {
  const std::vector<std::tuple<std::vector<int>, std::vector<int>,
                               std::vector<std::vector<int>>>>
      cases = {
          std::make_tuple(std::vector<int>({1, 1}), std::vector<int>({4, 5}),
                          std::vector<std::vector<int>>(
                              {{1, 2, 3, 3, 2}, {3, 4, 4, 5, 1}})),
          std::make_tuple(
              std::vector<int>({3, 2}), std::vector<int>({5, 7}),
              std::vector<std::vector<int>>(
                  {{3, 2, 3, 4, 4}, {3, 3, 5, 5, 5}, {3, 4, 5, 6, 6}})),
      };

  const std::vector<int> expects = {
      5,
      7,
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    int result =
        solution.MinimumCost(std::get<0>(cs), std::get<1>(cs), std::get<2>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}