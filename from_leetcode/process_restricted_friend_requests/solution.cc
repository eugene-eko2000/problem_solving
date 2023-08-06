#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "result_check/result_check.h"

class Solution {
private:
  class DisjointSetUnion {
  private:
    std::vector<int> ix_;
    std::vector<int> sz_;

  public:
    explicit DisjointSetUnion(int n) {
      ix_.resize(n);
      for (int i = 0; i < n; ++i) {
        ix_[i] = i;
      }
      sz_.resize(n, 1);
    }

    int FindGroup(int el) {
      int i = el;
      while (ix_[i] != i) {
        i = ix_[i];
      }
      return i;
    }

    int JoinGroups(int g1, int g2) {
      if (g1 == g2) {
        return g1;
      }
      int g_host = sz_[g1] < sz_[g2] ? g2 : g1;
      int g_join = sz_[g1] < sz_[g2] ? g1 : g2;

      sz_[g_host] += sz_[g_join];
      sz_[g_join] = 0;
      ix_[g_join] = g_host;
      return g_host;
    }
  };

public:
  std::vector<bool>
  FriendRequests(int n, const std::vector<std::vector<int>> &restrictions,
                 const std::vector<std::vector<int>> &requests) {
    DisjointSetUnion dsu(n);
    std::unordered_map<int, std::set<std::vector<int>>> group_restricts;
    for (const auto &r : restrictions) {
      group_restricts[r[0]].emplace(r);
      group_restricts[r[1]].emplace(r);
    }
    std::vector<bool> req_ok;
    for (const auto &req : requests) {
      int g1 = dsu.FindGroup(req[0]);
      int g2 = dsu.FindGroup(req[1]);
      if (g1 == g2) {
        req_ok.push_back(true);
        continue;
      }
      auto r1_it = group_restricts.find(g1);
      auto r2_it = group_restricts.find(g2);
      if (r1_it != group_restricts.end() && r2_it != group_restricts.end()) {
        std::vector<std::vector<int>> equals;
        set_intersection(r1_it->second.begin(), r1_it->second.end(),
                         r2_it->second.begin(), r2_it->second.end(),
                         std::back_inserter(equals));
        if (!equals.empty()) {
          req_ok.push_back(false);
          continue;
        }
      }
      int new_g = dsu.JoinGroups(g1, g2);
      req_ok.push_back(true);
      if (new_g == g1 && r2_it != group_restricts.end()) {
        group_restricts[new_g].insert(r2_it->second.begin(),
                                      r2_it->second.end());
        r2_it->second.clear();
      } else if (new_g == g2 && r1_it != group_restricts.end()) {
        group_restricts[new_g].insert(r1_it->second.begin(),
                                      r1_it->second.end());
        r1_it->second.clear();
      }
    }
    return req_ok;
  }
};

int main(int, char **) {
  const std::vector<std::tuple<int, std::vector<std::vector<int>>,
                               std::vector<std::vector<int>>>>
      cases = {
          std::make_tuple(3, std::vector<std::vector<int>>({{0, 1}}),
                          std::vector<std::vector<int>>({{0, 2}, {2, 1}})),
          std::make_tuple(3, std::vector<std::vector<int>>({{0, 1}}),
                          std::vector<std::vector<int>>({{1, 2}, {0, 2}})),
          std::make_tuple(
              5, std::vector<std::vector<int>>({{0, 1}, {1, 2}, {2, 3}}),
              std::vector<std::vector<int>>({{0, 4}, {1, 2}, {3, 1}, {3, 4}})),
      };

  const std::vector<std::vector<bool>> expects = {
      {true, false},
      {true, false},
      {true, false, true, false},
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::vector<bool> result = solution.FriendRequests(
        std::get<0>(cs), std::get<1>(cs), std::get<2>(cs));
    CheckResult(cs, expects[i], result);
  }
  return 0;
}