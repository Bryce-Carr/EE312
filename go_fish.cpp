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
#include <iostream>    // Provides cout and cin
#include <fstream>
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"
#include <ctime>
using namespace std;
ofstream gofish;

// pre: valid deck and player classes and number of cards input
// post: hand dealt to player
void dealHand(Deck &d, Player &p, int numCards) {
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}
// pre: 2 valid player classes
// post: prints who won
void gameOver(Player &p1, Player &p2) {
    int bookOne = p1.getBookSize();
    int bookTwo = p2.getBookSize();
    if (bookOne > bookTwo){
        cout << p1.getName() <<" wins!" << endl;
        gofish << p1.getName() <<" wins!" << endl;
    }
    else{
        cout << p2.getName() <<" wins!" << endl;
        gofish << p2.getName() <<" wins!" << endl;
    }
}
// pre: valid player class
// post: any pairs in hand are booked
void checkHand (Player &p){
    int handSize = p.getHandSize();
    for (int j = 0; j < handSize; ++j) {
        bool check = 0;
        Card choice = p.chooseCardFromHand(j);
        int rankChoice = choice.getRank();
        Card spade = Card(1, Card::spades);
        Card club = Card(1, Card::clubs);
        Card heart = Card(1, Card::hearts);
        Card diamond = Card(1, Card::diamonds);
        if(choice.sameSuitAs(spade) == 0){
            Card checkMatchSpades = Card(rankChoice, Card::spades);
            check = p.cardInHand(checkMatchSpades);
            if (check == 1 && p.cardInHand(choice) == 1) {
                p.bookCards(choice, checkMatchSpades);
                p.removeCardFromHand(choice);
                p.removeCardFromHand(checkMatchSpades);
                j = -1;
            }
        }
        if(choice.sameSuitAs(club) == 0){
            Card checkMatchClubs = Card(rankChoice, Card::clubs);
            check = p.cardInHand(checkMatchClubs);
            if (check == 1 && p.cardInHand(choice) == 1) {
                p.bookCards(choice, checkMatchClubs);
                p.removeCardFromHand(choice);
                p.removeCardFromHand(checkMatchClubs);
                j = -1;
            }
        }
        if(choice.sameSuitAs(heart) == 0){
            Card checkMatchHearts = Card(rankChoice, Card::hearts);
            check = p.cardInHand(checkMatchHearts);
            if (check == 1 && p.cardInHand(choice) == 1) {
                p.bookCards(choice, checkMatchHearts);
                p.removeCardFromHand(choice);
                p.removeCardFromHand(checkMatchHearts);
                j = -1;
            }
        }
        if(choice.sameSuitAs(diamond) == 0){
            Card checkMatchDiamonds = Card(rankChoice, Card::diamonds);
            check = p.cardInHand(checkMatchDiamonds);
            if (check == 1 && p.cardInHand(choice) == 1) {
                p.bookCards(choice, checkMatchDiamonds);
                p.removeCardFromHand(choice);
                p.removeCardFromHand(checkMatchDiamonds);
                j = -1;
            }
        }
        handSize = p.getHandSize();
    }
}
int main( )
{
    gofish.open ("gofish_results.txt");
    int numCards = 7; //for 2 players
    //player 1 always goes first
    Player p1("Joe");
    Player p2("Jane");

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, p1, numCards);
    checkHand(p1);

    dealHand(d, p2, numCards);
    checkHand(p2);

    cout << p1.getName() <<" starts with: " << p1.showHand() << endl;
    cout << p2.getName() <<" starts with: " << p2.showHand() << endl;
    gofish << p1.getName() <<" starts with: " << p1.showHand() << endl;
    gofish << p2.getName() <<" starts with: " << p2.showHand() << endl;
while(1) {
    int repeat = 1;
    while (repeat == 1) {
        if (p1.getHandSize() == 0) { //end game if all card gone
            if (d.size() == 0) {
                gameOver(p1, p2);
                gofish.close();
                return EXIT_SUCCESS;
            }
            //display game state
            Card drew = d.dealCard();
            p1.addCard(drew);
            cout << p2.getName() << "has no cards." << endl;
            cout << p1.getName() << " draws " << drew.toString() << endl;
            gofish << p2.getName() << "has no cards." << endl;
            gofish << p1.getName() << " draws " << drew.toString() << endl;
            checkHand(p1);
            repeat = 0;

        } else { //choose random card and display game state
            repeat = 0;
            srand(time(0));
            int number = p1.getHandSize();
            int random = rand() % number;
            Card choice = p1.chooseCardFromHand(random);
            int rankChoice = choice.getRank();
            string ask = choice.rankString(rankChoice);
            cout << p1.getName() << " asks: Do you have a " << ask << "?" << endl;
            gofish << p1.getName() << " asks: Do you have a " << ask << "?" << endl;
            //define cards of each suit
            Card spade = Card(1, Card::spades);
            Card club = Card(1, Card::clubs);
            Card heart = Card(1, Card::hearts);
            Card diamond = Card(1, Card::diamonds);
            bool check = 0;
            //next conditionals check if opponent has appropriate cards of matching rank; if so, take and book and display game state
            if(choice.sameSuitAs(spade) == 0) {
                Card checkMatchSpades = Card(rankChoice, Card::spades);
                check = p2.cardInHand(checkMatchSpades);
                if (check) {
                    p2.removeCardFromHand(checkMatchSpades);
                    p1.addCard(checkMatchSpades);
                    p1.bookCards(choice, checkMatchSpades);
                    p1.removeCardFromHand(choice);
                    p1.removeCardFromHand(checkMatchSpades);
                    repeat = 1;
                    cout << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p1.getName() << " books the " << ask << "." << endl;
                    gofish << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p1.getName() << " books the " << ask << "." << endl;
                }
            }
            //next conditionals check if opponent has appropriate cards of matching rank; if so, take and book and display game state
            if(choice.sameSuitAs(club) == 0) {
                Card checkMatchClubs = Card(rankChoice, Card::clubs);
                check = p2.cardInHand(checkMatchClubs);
                if (check) {
                    p2.removeCardFromHand(checkMatchClubs);
                    p1.addCard(checkMatchClubs);
                    p1.bookCards(choice, checkMatchClubs);
                    p1.removeCardFromHand(choice);
                    p1.removeCardFromHand(checkMatchClubs);
                    repeat = 1;
                    cout << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p1.getName() << " books the " << ask << "." << endl;
                    gofish << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p1.getName() << " books the " << ask << "." << endl;
                }
            }
            //next conditionals check if opponent has appropriate cards of matching rank; if so, take and book and display game state
            if(choice.sameSuitAs(heart) == 0) {
                Card checkMatchHearts = Card(rankChoice, Card::hearts);
                check = p2.cardInHand(checkMatchHearts);
                if (check) {
                    p2.removeCardFromHand(checkMatchHearts);
                    p1.addCard(checkMatchHearts);
                    p1.bookCards(choice, checkMatchHearts);
                    p1.removeCardFromHand(choice);
                    p1.removeCardFromHand(checkMatchHearts);
                    repeat = 1;
                    cout << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p1.getName() << " books the " << ask << "." << endl;
                    gofish << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p1.getName() << " books the " << ask << "." << endl;
                }
            }
            //next conditionals check if opponent has appropriate cards of matching rank; if so, take and book and display game state
            if(choice.sameSuitAs(diamond) == 0) {
                Card checkMatchDiamonds = Card(rankChoice, Card::diamonds);
                check = p2.cardInHand(checkMatchDiamonds);
                if (check) {
                    p2.removeCardFromHand(checkMatchDiamonds);
                    p1.addCard(checkMatchDiamonds);
                    p1.bookCards(choice, checkMatchDiamonds);
                    p1.removeCardFromHand(choice);
                    p1.removeCardFromHand(checkMatchDiamonds);
                    repeat = 1;
                    cout << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p1.getName() << " books the " << ask << "." << endl;
                    gofish << p2.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p1.getName() << " books the " << ask << "." << endl;
                }
            }
            //end game if cards gone
            if (repeat == 0) {
                if (d.size() == 0 && p1.getHandSize() == 0 && p2.getHandSize() == 0) {
                    gameOver(p1, p2);
                    gofish.close();
                    return EXIT_SUCCESS;
                }
                //draw card and display game state
                if (d.size() != 0){
                    Card drew = d.dealCard();
                    p1.addCard(drew);
                    cout << p2.getName() << " says: Go Fish" << endl;
                    cout << p1.getName() << " draws " << drew.toString() << endl;
                    gofish << p2.getName() << " says: Go Fish" << endl;
                    gofish << p1.getName() << " draws " << drew.toString() << endl;
                    checkHand(p1);
                }
            }
        }
    }
//same structure as previous loop but for other player
    repeat = 1;
    while (repeat == 1) {
        if (p2.getHandSize() == 0) {
            if (d.size() == 0) {
                gameOver(p1, p2);
                gofish.close();
                return EXIT_SUCCESS;
            }
            Card drew = d.dealCard();
            p2.addCard(drew);
            cout << p2.getName() << "has no cards." << endl;
            cout << p2.getName() << " draws " << drew.toString() << endl;
            gofish << p2.getName() << "has no cards." << endl;
            gofish << p2.getName() << " draws " << drew.toString() << endl;
            checkHand(p2);
            repeat = 0;
        } else {
            repeat = 0;
            srand(time(0));
            int number = p2.getHandSize();
            int random = rand() % number;
            Card choice = p2.chooseCardFromHand(random);
            int rankChoice = choice.getRank();
            string ask = choice.rankString(rankChoice);
            cout << p2.getName() << " asks: Do you have a " << ask << "?" << endl;
            gofish << p2.getName() << " asks: Do you have a " << ask << "?" << endl;

            Card spade = Card(1, Card::spades);
            Card club = Card(1, Card::clubs);
            Card heart = Card(1, Card::hearts);
            Card diamond = Card(1, Card::diamonds);
            bool check = 0;

            if(choice.sameSuitAs(spade) == 0) {
                Card checkMatchSpades = Card(rankChoice, Card::spades);
                check = p1.cardInHand(checkMatchSpades);
                if (check) {
                    p1.removeCardFromHand(checkMatchSpades);
                    p2.addCard(checkMatchSpades);
                    p2.bookCards(choice, checkMatchSpades);
                    p2.removeCardFromHand(choice);
                    p2.removeCardFromHand(checkMatchSpades);
                    repeat = 1;
                    cout << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p2.getName() << " books the " << ask << "." << endl;
                    gofish << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p2.getName() << " books the " << ask << "." << endl;
                }
            }
            if(choice.sameSuitAs(club) == 0) {
                Card checkMatchClubs = Card(rankChoice, Card::clubs);
                check = p1.cardInHand(checkMatchClubs);
                if (check) {
                    p1.removeCardFromHand(checkMatchClubs);
                    p2.addCard(checkMatchClubs);
                    p2.bookCards(choice, checkMatchClubs);
                    p2.removeCardFromHand(choice);
                    p2.removeCardFromHand(checkMatchClubs);
                    repeat = 1;
                    cout << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p2.getName() << " books the " << ask << "." << endl;
                    gofish << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p2.getName() << " books the " << ask << "." << endl;
                }
            }
            if(choice.sameSuitAs(heart) == 0) {
                Card checkMatchHearts = Card(rankChoice, Card::hearts);
                check = p1.cardInHand(checkMatchHearts);
                if (check) {
                    p1.removeCardFromHand(checkMatchHearts);
                    p2.addCard(checkMatchHearts);
                    p2.bookCards(choice, checkMatchHearts);
                    p2.removeCardFromHand(choice);
                    p2.removeCardFromHand(checkMatchHearts);
                    repeat = 1;
                    cout << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p2.getName() << " books the " << ask << "." << endl;
                    gofish << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p2.getName() << " books the " << ask << "." << endl;
                }
            }
            if(choice.sameSuitAs(diamond) == 0) {
                Card checkMatchDiamonds = Card(rankChoice, Card::diamonds);
                check = p1.cardInHand(checkMatchDiamonds);
                if (check) {
                    p1.removeCardFromHand(checkMatchDiamonds);
                    p2.addCard(checkMatchDiamonds);
                    p2.bookCards(choice, checkMatchDiamonds);
                    p2.removeCardFromHand(choice);
                    p2.removeCardFromHand(checkMatchDiamonds);
                    repeat = 1;
                    cout << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    cout << p2.getName() << " books the " << ask << "." << endl;
                    gofish << p1.getName() << " says: Yes. I have a " << ask << "." << endl;
                    gofish << p2.getName() << " books the " << ask << "." << endl;
                }
            }

            if (repeat == 0) {
                if (d.size() == 0 && p1.getHandSize() == 0 && p2.getHandSize() == 0) {
                    gameOver(p1, p2);
                    gofish.close();
                    return EXIT_SUCCESS;
                }
            }
            if (d.size() != 0){
                Card drew = d.dealCard();
                p2.addCard(drew);
                cout << p1.getName() << " says: Go Fish" << endl;
                cout << p2.getName() << " draws " << drew.toString() << endl;
                gofish << p1.getName() << " says: Go Fish" << endl;
                gofish << p2.getName() << " draws " << drew.toString() << endl;
                checkHand(p2);
            }
        }
    }
}
}