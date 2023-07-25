package main

import (
	"fmt"
)

func collectTheCoins(coins []int, edges [][]int) int {
  graph := make(map[int]map[int]bool)
  histCoins := make(map[int]int)
  histNonCoins := make(map[int]int)
  for _, e := range edges {
    if graph[e[0]] == nil {
      graph[e[0]] = make(map[int]bool)
    }
    if graph[e[1]] == nil {
      graph[e[1]] = make(map[int]bool)
    }
    graph[e[0]][e[1]] = true
    graph[e[1]][e[0]] = true
    if coins[e[1]] == 1 {
      histCoins[e[1]]++
    } else {
      histNonCoins[e[1]]++
    }
    if coins[e[0]] == 1 {
      histCoins[e[0]]++
    } else {
      histNonCoins[e[0]]++
    }
  }
  edgesNum := len(edges)
  for vertex, c := range histNonCoins {
    for c == 1 && coins[vertex] == 0 {
      peers := graph[vertex]
      // Getting the peer edge
      var peer int
      for e := range peers { peer = e }
      // Deleting the vertex and its edge
      delete(graph[peer], vertex)
      delete(graph, vertex)
      // Decrease edges count
      if edgesNum > 0 { edgesNum-- }
      // Decrease a number of edges at the coin vertex
      if coins[peer] == 1 { histCoins[peer]-- }
      // Set the peer as the current edge to proceed with the next step
      vertex = peer
      c = len(graph[peer])
    }
  }
  depths := map[int]int{}
  for vertex, c := range histCoins {
    depthCount := 0
    for c == 1 && depthCount < 2 && depths[vertex] < 2 {
      peers := graph[vertex]
      var peer int
      for e := range peers { peer = e }
      delete(graph[peer], vertex)
      delete(graph, vertex)
      if edgesNum > 0 { edgesNum-- }
      vertex = peer
      c = len(graph[peer])
      depthCount++
      if depths[peer] < depthCount { depths[peer] = depthCount }
    }
  }
  return edgesNum * 2
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
	Coins []int
	Edges [][]int
}

func main() {
	cases := []caseType{
		{
			[]int{1,0,0,0,0,1},
			[][]int{{0,1},{1,2},{2,3},{3,4},{4,5}},
		},
		{
			[]int{0,0,0,1,1,0,0,1},
			[][]int{{0,1},{0,2},{1,3},{1,4},{2,5},{5,6},{5,7}},
		},
	}

	expects := []int{
		2,
		2,
	}

	for i := range cases {
		result := collectTheCoins(cases[i].Coins, cases[i].Edges)
		testCaseResult(cases[i], expects[i], result)
	}
}
