#!/bin/bash

g++ -c main.cpp
g++ -c list.cpp
g++ main.o list.o -o main
./main < test.txt
