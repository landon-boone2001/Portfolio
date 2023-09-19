

// main.cpp / CardDeck.cpp 
// This program will create a card deck, draw 10 initial cards, display them, shuffle those cards, then display the shuffled 10 cards.
// After this demonstration, the deck will be deleted, and a new deck will be instantiated. This deck will be used to play a game of blackjack 
// between two players: the user, and a computer player, the "house"/dealer.
// The program will deal two cards to the player, displaying the cards drawn and the card value total, then will ask for one of three inputs: 
// Hit 'h', Stand 's', or quit 'q' If the user enters h, another card will be drawn, displayed, and added to the total card value. If the 
// total value of the cards of the user or the house are above 21, the program will automatically grant a win to the opposite player, and prompt
// the player for a rematch offer. If the player chooses to stand, their turn will end and move on to the house. The house will automatically
// stand at 17. When both players stand, the total cards value for each player will be compared, and the program will tell the user if they 
// win, lose, or tied with the House, before being prompted for a rematch. At the beginning of each game, a scoreboard is displayed
// telling the score of the wins of the player and the house in previous matches, and the amount of times they have tied.
// Landon Boone - CS 202
// 8-26-22

// ***Used framework provided by Blake Childress in lab 3 powerpoint*** 

#include "CardDeck.h"
#include <iostream>
using namespace std;


int main() {
    int dealtCard;
    int playerWins = 0;
    int dealerWins = 0;
    int ties = 0;
    char input;

    bool bustCheck = false;
    bool running = true;
    bool rematchCheck = true;
    bool playerHit = true;
    bool dealerHit = true;

    srand (time(NULL) );
    CardDeck *deck;
    deck = new CardDeck(10);
    deck->display();
    deck->shuffle();
    deck->display();
    delete deck;
    printf("\n");

    deck = new CardDeck();
    deck->shuffle();

    do {

        bustCheck = false;
        playerHit = true;
        dealerHit = true;
        int playerHandSize = 2;
        int dealerHandSize = 2;
        int playerHand[playerHandSize];
        int dealerHand[playerHandSize];
        int playerTotal = 0;
        int dealerTotal = 0;
        playerHand[0] = 0;
        dealerHand[0] = 0;
        //check for fewer than 15 cards
        if(deck->getSize() < 15) {
            delete deck;
            deck = new CardDeck();
            for(int i = 0; i < (rand() % 10) + 1; i++) deck->shuffle(); //shuffle 1-10 times
        
        }
        
        printf("-----------------------------------\n");
        printf("player [%d] | house [%d] | tie [%d]\n", playerWins, dealerWins, ties);
        printf("-----------------------------------\n");
        //deals the initial 2 cards to the user
        for (int i = 0; i < 2; i++) {
            playerHand[i] = deck->deal(playerHand, playerHandSize, deck->getSize());
        }

        cout << "You have been dealt a " << playerHand[0] << " and a " << playerHand[1] << ". " << endl;
        playerTotal = playerHand[0]+playerHand[1];

        while (playerHit) {
            
            cout << "Your card total is " << playerTotal << ". " << endl;
            cout << "Type 'h' to hit, 's' to stand, or 'q' to quit: "; 
            cin >> input;

            if (input == 'h') {
                dealtCard = 0;
                dealtCard = deck->deal(playerHand, playerHandSize, deck->getSize());
                playerTotal += dealtCard;
                //checks for 11 to output proper grammer
                if (dealtCard == 11) {
                    cout << "You drew an " << dealtCard << "." << std::endl;
                }
                else {
                    cout << "You drew a " << dealtCard << "." << std::endl;
                }
                playerHandSize++;

            }
        
            else if (input == 's') {
                cout << "You have chosen to stand." << endl;
                playerHit = false;
            }

            else if (input == 'q') {
                cout << "quitting...";
                return 0;
            }

            else {
                cout << "Error: invalid input.";
            }

            if (playerTotal > 21) {
                bustCheck = true;
                cout << "Your card total is " << playerTotal << ". " << endl;
                playerHit = false;
                dealerHit = false;
                dealerWins++;
                cout << "You busted; The house wins. Play Again? Please enter 'y' to continue, otherwise enter 'q' to quit: ";
                cin >> input;
                
                if (input == 'y' ){
                    break;
                }
                
                else if (input == 'q') { 
                    cout << "Thank you for playing. Quitting..." << endl;
                    return 0;
                }
               
                else {
                    cout << "Error: Unknown input." << endl;
                }
            }
            
        }
        //checks to see if the player busted. if not, deals 2 cards to dealer
        if (dealerHit == true) {
            for (int i = 0; i < 2; i++) {
                dealerHand[i] = deck->deal(dealerHand, dealerHandSize, deck->getSize());
            }

            cout << "The house has drawn a " << dealerHand[0] << " and a " << dealerHand[1] << ". " << endl;
            dealerTotal = dealerHand[0]+dealerHand[1];
        }
        // dealer automatically stands at 17
        while (dealerHit) {
            if (dealerTotal < 17){
                cout << "The House's card total is " << dealerTotal << ". " << endl;
                dealtCard = 0;
                dealtCard = deck->deal(dealerHand, dealerHandSize, deck->getSize());
                dealerTotal += dealtCard;
                
                
                if (dealtCard == 11) {
                    cout << "The House drew an " << dealtCard << "." << std::endl;
                }
                else {
                    cout << "The House drew a " << dealtCard << "." << std::endl;
                }
                
                dealerHandSize++;
            }

            else if (dealerTotal > 21) {
                bustCheck = true;
                cout << "The House's card total is " << dealerTotal << ". " << endl;
                dealerHit = false;
                playerHit = false;
                playerWins++;
                cout << "The House busted; You Win! Play Again? Please enter 'y' to continue, otherwise enter 'q' to quit: ";
                
                cin >> input;
                
                if (input == 'y' ){
                    break;
                }
                
                else if (input == 'q') { 
                    cout << "Thank you for playing. Quitting..." << endl;
                    return 0;
                }
               
                else {
                    cout << "Error: Unknown input." << endl;
                }
            }

            else {
                cout << "The House's card total is " << dealerTotal << ". " << endl;
                dealerHit = false;
            }

        }
        //all win conditions check for bust from player / house to prevent reading out a win twice.
        if (bustCheck == false && playerTotal > dealerTotal) {
            cout << "You win! Play Again? Please enter 'y' to continue, otherwise enter 'q' to quit: ";
            playerWins++;
                
            cin >> input;
            
            if (input == 'y' ){
                running = true;
            }
            
            else if (input == 'q') { 
                cout << "Thank you for playing. Quitting..." << endl;
                return 0;
            }
            
            else {
                cout << "Error: Unknown input." << endl;
            }
        }
        
        else if (bustCheck == false && dealerTotal > playerTotal) {
            cout << "You lose. Play Again? Please enter 'y' to continue, otherwise enter 'q' to quit: ";
            dealerWins++;
                
            cin >> input;
            
            if (input == 'y' ){
                running = true;
            }
            
            else if (input == 'q') { 
                cout << "Thank you for playing. Quitting..." << endl;
                return 0;
            }
            
            else {
                cout << "Error: Unknown input." << endl;
            }
        }
      
        else if (bustCheck == false && dealerTotal == playerTotal) {
            cout << "You tied with the house. Play Again? Please enter 'y' to continue, otherwise enter 'q' to quit: ";
            ties++;
                
            cin >> input;
            
            if (input == 'y' ){
                running = true;
            }
            
            else if (input == 'q') { 
                cout << "Thank you for playing. Quitting..." << endl;
                return 0;
            }
            
            else {
                cout << "Error: Unknown input." << endl;
            }
        }

    } while (running);

}