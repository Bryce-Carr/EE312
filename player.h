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
// FILE:  player.h
// written by Bryce Carr
// 11/9/2018
// This class represents a player in a card game that takes "tricks"
// The "Books" represent a container for holding tricks

#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <string>
#include <vector>


#include "card.h"
using namespace std;


class Player
{
public:
    //constructors
    Player(){
        myName = "Doe";
    }

    Player(string name) {
        myName = name;
    }

    string getName() const { //return player name
        return myName;
    }

    void addCard(Card c){ //add card to player hand vector
        myHand.push_back(c);
    }  //adds a card to the hand

    void bookCards(Card c1, Card c2){ //book a pair of cards for player
        myBook.push_back(c1);
        myBook.push_back(c2);
    }

    //OPTIONAL
    // comment out if you decide to not use it
    //this function will check a players hand for a pair.
    //If a pair is found, it returns true and populates the two variables with the cards that make the pair.

    /*bool checkHandForBook(Card &c1, Card &c2){
        int check1 = c1.getRank();
        int check2 = c2.getRank();
        if
    }*/

    //OPTIONAL
    // comment out if you decide to not use it
    //Does the player have a card with the same rank as c in her hand?
    /*bool rankInHand(Card c) const{
        int handSize = getHandSize();
        int check1 = c.getRank();
        int check2 = 0;
        for (int i = 0; i < handSize; ++i) {
            check2 = myHand[i].getRank();
            if (check1 == check2){
                return 1;
            }
        }
        return 0;
    }*/

    //uses some strategy to choose one card from the player's
    //hand so they can say "Do you have a 4?"
    Card chooseCardFromHand(int num) const{
        Card value = myHand[num];
        return value;
    }

    //Does the player have the card c in her hand?
    bool cardInHand(Card c) const{
        int handSize = getHandSize();
        for (int i = 0; i < handSize; ++i) {
            Card temp = myHand[i];
            if(c == temp){
                return 1;
            }
        }
        return 0;
    }

    //Remove the card c from the hand and return it to the caller
    Card removeCardFromHand(Card c){
        int handSize = getHandSize();
        Card value;
        for (int i = 0; i < handSize; ++i) {
            value = myHand[i];
            if(value == c){
                myHand.erase(myHand.begin()+i);
                return value;
            }
        }
    }

    string showHand() const{ //puts hand of cards into string
        int handSize = getHandSize();
        string value = "";
        string temp2 = "";
        for (int i = 0; i < handSize; ++i) {
            Card temp = myHand[i];
            temp2 = temp.toString();
            value = value+" "+temp2;
        }
        return value;
    }
    string showBooks() const{ //puts player's book into string
        int bookSize = getBookSize();
        string value = "";
        string temp2 = "";
        for (int i = 0; i < bookSize; ++i) {
            Card temp = myBook[i];
            temp2 = temp.toString();
            value = value+" "+temp2;
        }
        return value;
    }

    int getHandSize() const{
        int size = myHand.size();
        return size;
    }

    int getBookSize() const{
        int size = myBook.size();
        size /=2;
        return size;
    }

    //OPTIONAL
    // comment out if you decide to not use it
    //this function will check a players hand for a pair.
    //If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

    //bool checkHandForPair(Card &c1, Card &c2);

    //OPTIONAL
    // comment out if you decide to not use it
    //Does the player have a card with the same rank as c in her hand?
    //e.g. will return true if the player has a 7d and the parameter is 7c

    //bool sameRankInHand(Card c) const;


private:

    vector <Card> myHand;
    vector <Card> myBook;

    string myName;

};


#endif