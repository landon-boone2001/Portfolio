#!/bin/bash
g++ -c main.cpp
g++ -c -o CardDeck.o CardDeck.cpp
g++ main.o CardDeck.o -o main
rm main.o
rm cardDeck.o
./main