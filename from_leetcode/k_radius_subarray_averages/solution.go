package main

import (
	"fmt"
	"reflect"
)

func getAverages(nums []int, k int) []int {
	res := make([]int, len(nums))
	for i := range nums {
		res[i] = -1
	}
	if k*2+1 > len(nums) {
		return res
	}
	currSum := 0
	for _, v := range nums[:k] {
		currSum += v
	}
	for center := 0; center < len(nums); center++ {
		if center+k < len(nums) {
			currSum += nums[center+k]
		}
		if center-k > 0 {
			currSum -= nums[center-k-1]
		}
		if center-k >= 0 && center+k < len(nums) {
			res[center] = currSum / (2*k + 1)
		}
	}
	return res
}

func testCaseResult(cs caseType, expect, result []int) {
	fmt.Println("Case:", cs)
	if reflect.DeepEqual(result, expect) {
		fmt.Println("Expected:", expect, "test PASSED.")
	} else {
		fmt.Println("Expected:", expect, "result: ", result, "test FAILED!")
	}
}

type caseType struct {
	Nums []int
	K    int
}

func main() {
	cases := []caseType{
		{
			[]int{7, 4, 3, 9, 1, 8, 5, 2, 6},
			3,
		},
		{
			[]int{100000},
			0,
		},
		{
			[]int{8},
			100000,
		},
	}

	expects := [][]int{
		{-1, -1, -1, 5, 4, 4, -1, -1, -1},
		{100000},
		{-1},
	}

	for i := range cases {
		result := getAverages(cases[i].Nums, cases[i].K)
		testCaseResult(cases[i], expects[i], result)
	}
}
