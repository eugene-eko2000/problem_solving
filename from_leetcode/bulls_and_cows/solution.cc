#include <sstream>
#include <string>

#include "result_check/result_check.h"

class Solution {
public:
  std::string GetHint(std::string secret, std::string guess) {
    int b = 0, c = 0;
    for (int i = 0; i < guess.size(); ++i) {
      if (secret[i] == guess[i]) {
        ++b;
        secret[i] = 'z';
        guess[i] = 'z';
      }
    }
    sort(secret.begin(), secret.end());
    sort(guess.begin(), guess.end());
    int i = 0;
    int j = 0;
    for (; i < secret.size() && j < guess.size() && secret[i] != 'z' && guess[j] != 'z';) {
      if (secret[i] < guess[j]) {
        ++i;
      } else if(guess[j] < secret[i]) {
        ++j;
      } else {
        ++c;
        ++i;
        ++j;
      }
    }
    std::stringstream buf;
    buf << b << "A" << c << "B";
    return buf.str();
  }
};

int main() {
  const std::vector<std::pair<std::string, std::string>> cases = {
      std::make_pair("1807", "7810"),
      std::make_pair("1123", "0111"),
  };

  const std::vector<std::string> expects = {
      "1A3B",
      "1A1B",
  };

  Solution solution;

  for (int i = 0; i < cases.size(); ++i) {
    const auto &cs = cases[i];
    std::string result = solution.GetHint(cs.first, cs.second);
    CheckResult(cs, expects[i], result);
  }
  return 0;
}