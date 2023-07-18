package main

import (
	"fmt"
)

func maxProfit(prices []int, fee int) int {
  minPrice := prices[0]
  maxPrice := prices[0]
  profit := 0
  for i := 0; i < len(prices) - 1; i++ {
    if maxPrice > prices[i + 1] + fee && maxPrice - minPrice - fee > 0 {
      profit += maxPrice - minPrice - fee
      minPrice = prices[i + 1]
      maxPrice = prices[i + 1]
    }
    if prices[i + 1] < minPrice {
      minPrice = prices[i + 1]
      maxPrice = prices[i + 1]
    } 
    if prices[i + 1] > maxPrice {
      maxPrice = prices[i + 1]
    }
  }
  if maxPrice - minPrice - fee > 0 {
    profit += maxPrice - minPrice - fee
  }
  return profit
}

func testCaseResult(cs caseType, expect, result int) {
	fmt.Println("Case:", cs)
	if result == expect {
		fmt.Println("Expected:", expect, "test PASSED.")
	} else {
		fmt.Println("Expected:", expect, "result: ", result, "test FAILED!")
	}
}

type caseType struct {
	Prices []int
	Fee int
}

func main() {
	cases := []caseType{
		{
			[]int{1, 3, 2, 8, 4, 9},
			2,
		},
		{
			[]int{1, 3, 7, 5, 10, 3},
			3,
		},
	}

	expects := []int{8, 6}

	for i := range cases {
		result := maxProfit(cases[i].Prices, cases[i].Fee)
		testCaseResult(cases[i], expects[i], result)
	}
}
