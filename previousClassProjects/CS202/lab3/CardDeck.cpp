//Provided by CS302 - Blake Childress, Dr. Scott Emrich
#include <iostream>
#include <algorithm>
#include <time.h>
#include "CardDeck.h"


CardDeck::CardDeck(int n) {
    size = n;
    deck = new int[size];

    for(int i = 0; i < n; i++) {
        deck[i] = (i % 13) + 1;
    }
}


const CardDeck &CardDeck::operator=(const CardDeck &obj) {
    if(&obj != this) {
        if (size != obj.size) {
            delete [] deck;
            size = obj.size;
            deck = new int[size];
        }
    }
   
    for (int i = 0; i < size; i++) {
        deck[i] = *obj.deck;
    }

    return (*this);
}

CardDeck::~CardDeck() {
    delete [] deck;

}

void CardDeck::shuffle() {
    std::random_shuffle(&deck[0], &deck[size]);
}

int CardDeck::getSize() {
    return size;
}

void CardDeck::display() {
    for (int i = 0; i < size; i++) {
        std::cout << deck[i] << " " ;
    }
}

int CardDeck::deal(int hand[], int handSize, int deckSize) {

    int drawnCardIndex;
    int drawnCard;

    int newHand[handSize+1];
    for (int i = 0; i < handSize; i++) {
        newHand[i] = hand[i];
    }
    //sets Ace cards equal to 11 permenantly
    drawnCardIndex = rand() % deckSize;
    if (deck[drawnCardIndex] == 1) {
        drawnCard = 11;
    }
    //sets Jack, King, and Queen equal to 10 permenantly
    else if (deck[drawnCardIndex] == 11 || deck[drawnCardIndex] == 12 || deck[drawnCardIndex] == 13) {
        drawnCard = 10;
    }
    else {
        drawnCard = deck[drawnCardIndex];
    }
    hand[handSize+1] = deck[drawnCardIndex];
    return drawnCard;
}