package main

import (
	"fmt"
)

type UnionFind struct {
	ix []int
	gr map[int][]int
}

func NewUnionFind(n int) *UnionFind {
	uf := UnionFind{
		make([]int, n),
		make(map[int][]int),
	}
	for i := 0; i < len(uf.ix); i++ {
		uf.ix[i] = i
		uf.gr[i] = append(uf.gr[i], i)
	}
	return &uf
}

func (uf *UnionFind) Union(u, v int) {
	ug := uf.Find(u)
	vg := uf.Find(v)
	if ug == vg {
		return
	}
	if len(uf.gr[ug]) > len(uf.gr[vg]) {
		uf.ix[vg] = ug
		uf.gr[ug] = append(uf.gr[ug], uf.gr[vg]...)
		delete(uf.gr, vg)
	} else {
		uf.ix[ug] = vg
		uf.gr[vg] = append(uf.gr[vg], uf.gr[ug]...)
		delete(uf.gr, ug)
	}
}

func (uf *UnionFind) Find(v int) int {
	root := v
	for uf.ix[root] != root {
		root = uf.ix[root]
	}
	return root
}

func (uf *UnionFind) Groups() map[int][]int {
	return uf.gr
}

type FindCycleContext struct {
	graph        []int
	visited      map[int]int
	uf           *UnionFind
	cycleSize    int
	pathLength   int
	cycleVertex1 int
	cycleVertex2 int
}

func NewFindCycleContext(fav []int) *FindCycleContext {
	c := FindCycleContext{
		fav,
		make(map[int]int),
		NewUnionFind(len(fav)),
		0,
		0,
		-1,
		-1,
	}
	for i, v := range fav {
		c.uf.Union(i, v)
	}
	return &c
}

func (context *FindCycleContext) dfs(vertex int) {
	if v, ok := context.visited[vertex]; ok {
		context.cycleSize = context.pathLength - v
		if context.cycleSize == 2 {
			context.cycleVertex1 = vertex
			context.cycleVertex2 = context.graph[vertex]
		}
		return
	}
	context.visited[vertex] = context.pathLength
	context.pathLength++
	context.dfs(context.graph[vertex])
}

type MaxPathContext struct {
	rGraph        [][]int
	cycleVertice1 int
	cycleVertice2 int
	visited       map[int]bool
	maxLength     int
}

func NewMaxPathContext(sg []int, cv1, cv2 int) *MaxPathContext {
	c := MaxPathContext{
		make([][]int, len(sg)),
		cv1,
		cv2,
		make(map[int]bool),
		0,
	}
	for i, v := range sg {
		c.rGraph[v] = append(c.rGraph[v], i)
	}
	return &c
}

func (context *MaxPathContext) findMaxPath() int {
	context.visited = make(map[int]bool)
	context.visited[context.cycleVertice2] = true
	context.dfs(context.cycleVertice1, 0)
	path1 := context.maxLength
	context.maxLength = 0
	context.visited = make(map[int]bool)
	context.visited[context.cycleVertice1] = true
	context.dfs(context.cycleVertice2, 0)
	path2 := context.maxLength
	return path1 + path2
}

func (context *MaxPathContext) dfs(vertex int, length int) {
	if _, ok := context.visited[vertex]; ok {
		return
	}
	length += 1
	if context.maxLength < length {
		context.maxLength = length
	}
	for _, v := range context.rGraph[vertex] {
		context.dfs(v, length)
	}
}

func maximumInvitations(favorite []int) int {
	context := NewFindCycleContext(favorite)

	longestCyclePath := 0
	nonCyclePath := 0
	for _, g := range context.uf.Groups() {
		context.dfs(g[0])
		if context.cycleSize > 2 {
			if longestCyclePath < context.cycleSize {
				longestCyclePath = context.cycleSize
			}
			continue
		}
		maxPathContext := NewMaxPathContext(
			favorite,
			context.cycleVertex1,
			context.cycleVertex2)
		newPath := maxPathContext.findMaxPath()
		nonCyclePath += newPath
	}

	if longestCyclePath > nonCyclePath {
		return longestCyclePath
	}
	return nonCyclePath
}

func testCaseResult(cs []int, expect, result int) {
	fmt.Println("Case:", cs)
	if result == expect {
		fmt.Println("Expected:", expect, "test PASSED.")
	} else {
		fmt.Println("Expected:", expect, "result: ", result, "test FAILED!")
	}
}

func main() {
	cases := [][]int{
		{2, 2, 1, 2},
		{1, 2, 0},
		{3, 0, 1, 4, 1},
	}

	expects := []int{
		3,
		3,
		4,
	}

	for i := range cases {
		result := maximumInvitations(cases[i])
		testCaseResult(cases[i], expects[i], result)
	}
}
