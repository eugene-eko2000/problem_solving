#ifndef __PROBLEM_SOLVING_RESULT_CHECK_H__
#define __PROBLEM_SOLVING_RESULT_CHECK_H__

#include <iostream>

#include "prettyprint.hpp"

template<class Case, class Expect, class Result>
void CheckResult(const Case &cs,
                  const Expect &expect,
                  const Result &result) {
  std::cout << "Case: " << cs << "\n";
  if (expect == result) {
    std::cout << "Expected: " << expect << ", test PASSED.\n";
  } else {
    std::cout << "Expected: " << expect << ", result: " << result
              << ", test FAILED!\n";
  }
}

#endif  // __PROBLEM_SOLVING_RESULT_CHECK_H__