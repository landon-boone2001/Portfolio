CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		nqueens

nqueens:	nqueens.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f nqueens

test:		test-8 test-10

test-8:	nqueens
	@echo Testing board size of 8 input/output...
	@diff --suppress-common-lines -y <(./nqueens 8) output

test-10: nqueens
	@echo Testing board size of 10 input/output...
	@diff --suppress-common-lines -y <(./nqueens 10) output2
