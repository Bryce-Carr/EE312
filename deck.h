/* prog06_blc2829.c
// -- EE 312 Project 6 Go Fish

 Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, Bryce, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Bryce Carr
 * email address: brycecarr@utexas.edu
 * UTEID: blc2829
 * Section 5 digit ID: 16195
 * */
// FILE: deck.h
// written by Bryce Carr
// 11/9/2018
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck will randomize whatever cards are in the deck
// Do not shuffle if you have less than 2 cards
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//

#ifndef _DECK_H
#define _DECK_H

#include "card.h"
#include <math.h>
#include <ctime>


class Deck
{
    static const int SIZE = 52;

public:


    Deck(){
        myIndex = 0;
        for (int i = 1; i <= 13; ++i) {
                myCards[i-1] = Card(i, Card::spades);
        }
        for (int i = 1; i <= 13; ++i) {
            myCards[i+12] = Card(i, Card::clubs);
        }
        for (int i = 1; i <= 13; ++i) {
            myCards[i+25] = Card(i, Card::hearts);
        }
        for (int i = 1; i <= 13; ++i) {
            myCards[i+38] = Card(i, Card::diamonds);
        }
    }           // pristine, sorted deck

    void shuffle(){
        int number = SIZE-myIndex;
        if (number <=2){
            return;
        }
        int r1, r2 = 0;
        srand(time(0));
        for(int i=0; i < number*10; i++) {
            r1 = rand() % number;
            r2 = rand() % number;
            Card saved = myCards[r1];
            myCards[r1] = myCards[r2];
            myCards[r2] = saved;
        }
    }   // shuffle the cards in the current deck

    Card dealCard() {
        if (size() != 0) {
            myIndex = myIndex + 1;
            Card value = myCards[myIndex];
            return value;
        }
        else{
            cout << "Deck empty. Game over." << endl;
        }
    }   // get a card, after 52 are dealt, fail

    int  size() const{
        int value = 51 - myIndex;
        return value;
    } // # cards left in the deck

private:

    Card myCards[SIZE]; //array of Cards in deck
    int myIndex;  // current card to deal
};

#endif