package main

import (
	"fmt"
)

func minimumCost(s string) int64 {
  n := len(s)
  mid := n / 2
  cost := 0
  for i := mid - 1; i >= 0; i-- {
    if s[i] == s[i + 1] {
      continue
    }
    cost += i + 1
  }
  for i := mid + 1; i < n; i++ {
    if s[i] == s[i - 1] {
      continue
    }
    cost += n - i
  }
  return int64(cost)
}

func testCaseResult(cs string, expect, result int64) {
	fmt.Println("Case:", cs)
	if result == expect {
		fmt.Println("Expected:", expect, "test PASSED.")
	} else {
		fmt.Println("Expected:", expect, "result: ", result, "test FAILED!")
	}
}

type caseType struct {
	Coins []int
	Edges [][]int
}

func main() {
	cases := []string{
    "0011",
    "010101",
	}

	expects := []int64{
		2,
		9,
	}

	for i := range cases {
		result := minimumCost(cases[i])
		testCaseResult(cases[i], expects[i], result)
	}
}
