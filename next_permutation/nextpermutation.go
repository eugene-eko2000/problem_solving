package main

import (
	"fmt"
	"reflect"
	"sort"
)

func nextPermutation(nums []int)  {
  var i int
  for i = len(nums) - 1; i > 0 && nums[i - 1] >= nums[i]; i-- {}
  if i > 0 {
    var j int
    k := nums[i]
    ki := i
    for j = i; j < len(nums); j++ {
      if nums[j] > nums[i - 1] && nums[j] < k {
        ki = j
        k = nums[j]
      }
    }
    t := nums[i - 1]
    nums[i - 1] = nums[ki]
    nums[ki] = t
  }
  sort.Ints(nums[i:])
}

func testCaseResult(expect, result []int) {
	if reflect.DeepEqual(result, expect) {
		fmt.Println("Expected:", expect, "test PASSED");
	} else {
		fmt.Println("Expected:", expect, "result: ", result, "test FAILED");
	}
}

func main() {
	cases := [][]int {
		{1, 2, 3},
		{3, 2, 1},
		{1, 1, 5},
	}
	
	expects := [][]int {
		{1, 3, 2},
		{1, 2, 3},
		{1, 5, 1},
	}

	for i := range cases {
		nextPermutation(cases[i]);
		testCaseResult(expects[i], cases[i]);
	}
}