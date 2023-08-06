#include <iostream>
#include <map>
#include <vector>

#include "prettyprint.hpp"

class FenwickTree {
private:
  std::vector<int64_t> fwt_;

public:
  explicit FenwickTree(int64_t capacity) : fwt_(capacity) {}

  void Update(int64_t index, int value) {
    while (index < fwt_.size()) {
      fwt_[index] += value;
      index += index & -index;
    }
  }

  int64_t Query(int64_t index) {
    int64_t result = 0;
    while (index > 0) {
      result += fwt_[index];
      index -= index & -index;
    }
    return result;
  }
};

class EventsOnTimeline {
private:
  std::vector<FenwickTree> data_;
  static constexpr uint64_t kTimelineSize = 1000000; 

public:
  EventsOnTimeline() {
    for (int i =0; i < 12; ++i) {
      data_.emplace_back(kTimelineSize);
    }
  }
  void AddEvent(int64_t year, int magnitude) {
    if (year >= kTimelineSize) {
      std::cout << "Error: the year exceeds the timeline size.\n";
      return;
    }
    if (magnitude > 12) {
      std::cout << "Error: the magnitude cannot exceed 12.\n";
      return;
    }
    data_[magnitude - 1].Update(year, 1);
  }

  std::map<int, int64_t> NumEvents(int64_t year_start, int64_t year_end) {
    std::map<int, int64_t> result;
    if (year_end >= kTimelineSize) {
      std::cout << "Error: the year_end exceeds the timeline size.\n";
      return result;
    }
    if (year_end < year_start) {
      std::cout << "Error: the year_start cannot exceed the year_end.\n";
      return result;
    }
    for (int m = 0; m < 12; ++m) {
      int64_t cnt = data_[m].Query(year_end) - data_[m].Query(year_start);
      if (cnt > 0) {
        result[m + 1] = cnt;
      }
    }
    return result;
  }
};

int main() {
  EventsOnTimeline eot;

  eot.AddEvent(12, 7);
  eot.AddEvent(12, 7);
  eot.AddEvent(12, 6);
  eot.AddEvent(12, 8);
  eot.AddEvent(12, 3);
  eot.AddEvent(12, 7);
  eot.AddEvent(12, 4);
  eot.AddEvent(12, 3);
  eot.AddEvent(12, 9);
  eot.AddEvent(989, 6);
  eot.AddEvent(321, 4);
  eot.AddEvent(888, 2);
  eot.AddEvent(657, 4);
  eot.AddEvent(89, 7);
  eot.AddEvent(432, 10);
  eot.AddEvent(786, 10);
  eot.AddEvent(989, 2);
  eot.AddEvent(123, 5);
  eot.AddEvent(787564, 11);
  eot.AddEvent(562763, 13);
  eot.AddEvent(875643, 4);
  eot.AddEvent(67348276, 4);

  std::cout << "10 - 100:" << eot.NumEvents(10, 100) << "\n";
  std::cout << "87 - 89:" << eot.NumEvents(87, 89) << "\n";
  std::cout << "0 - 999999:" << eot.NumEvents(0, 999999) << "\n";
  std::cout << "500 - 600:" << eot.NumEvents(500, 600) << "\n";

  return 0;
}