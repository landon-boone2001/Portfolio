#!/bin/bash
g++ -c main.cpp
g++ -c C4Col.cpp
g++ -c C4Board.cpp
g++ main.o C4Col.o C4Board.o -o main
./main