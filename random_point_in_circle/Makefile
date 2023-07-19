preinstall:
	mkdir -p .output

build: preinstall
	g++ -std=gnu++17 -o .output/solution.bin solution.cc

run: build
	.output/solution.bin