all: treematch

CXX ?= clang++

treematch: treematch.C
	$(CXX) --std=c++11 -o treematch treematch.C

clean:
	rm treematch
