//Provided by CS302 - Blake Childress, Dr. Scott Emrich
#ifndef CARDDECK_H
#define CARDDECK_H

class CardDeck{
    private:
        int *deck;
        int size;
    public: 
        CardDeck(int n = 52);
        CardDeck(const CardDeck &obj);
        ~CardDeck();
        
        const CardDeck &operator=(const CardDeck &obj);

        int getSize();
        void shuffle();
        void display();
        int deal(int hand[], int handSize, int deckSize);
};

#endif