#include <iostream>
#include <random> 
#include <string>
#include <vector>

class Solution {
private:
  double radius_;
  double x_center_;
  double y_center_;

  std::random_device r_;

public:
    Solution(double radius, double x_center, double y_center)
        : radius_(radius), x_center_(x_center), y_center_(y_center) {
    }
    std::vector<double> RandPoint() {
      std::default_random_engine e1 = std::default_random_engine(r_());
      std::uniform_real_distribution angle_dist(0.0, 2 * 3.1415927);
      double angle = angle_dist(e1);
      double sin_a = sin(angle);
      double cos_a = cos(angle);

      std::uniform_real_distribution radius_dist(0.0, radius_ * radius_);
      double rad_piece = sqrt(radius_dist(e1));
      double x = rad_piece * sin_a + x_center_;
      double y = rad_piece * cos_a + y_center_;

      return {x, y};
    }
};

int main(int, char **) {
  Solution solution(1.0, 0.0, 0.0);

  for (int i = 0; i < 100; ++i) {
    std::vector<double> result = solution.RandPoint();
    std::cout << result[0] << "," << result[1] << "\n";
  }
  return 0;
}