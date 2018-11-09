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
//File Name: card.h
//
// written by Bryce Carr
// 11/9/2018
// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13

#ifndef _CARD_H
#define _CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card
{
public:


    enum Suit {spades, hearts, diamonds, clubs};

    Card(){
        mySuit = spades;
        myRank = 1;
    }          // default, ace of spades

    Card(int rank, Suit s){
        mySuit = s;
        myRank = rank;
    }

    string toString()              const{
        string value = "";
        string rankValue = rankString(myRank);
        string suitValue = suitString(mySuit);
        return value = rankValue+suitValue;
    }// return string version e.g. Ac 4h Js

    bool sameSuitAs(const Card& c) const{
        if (mySuit == c.mySuit){
            return 1;
        }
        else{
            return 0;
        }
    }  // true if suit same as c

    int  getRank()                 const{
        return myRank;
    }  // return rank, 1..13

    string suitString(Suit s)      const{
        string value = "";
        if (s == spades) {
            value = "s";
        }
        if (s == clubs) {
            value = "c";
        }
        if (s == hearts) {
            value = "h";
        }
        if (s == diamonds) {
            value = "d";
        }
        return value;
    }  // return "s", "h",...

    string rankString(int r)       const{
        string value = "";
        if (r == 1) {
            value = "A";
        }
        if (r == 2) {
            value = "2";
        }
        if (r == 3) {
            value = "3";
        }
        if (r == 4) {
            value = "4";
        }
        if (r == 5) {
            value = "5";
        }
        if (r == 6) {
            value = "6";
        }
        if (r == 7) {
            value = "7";
        }
        if (r == 8) {
            value = "8";
        }
        if (r == 9) {
            value = "9";
        }
        if (r == 10) {
            value = "10";
        }
        if (r == 11) {
            value = "J";
        }
        if (r == 12) {
            value = "Q";
        }
        if (r == 13) {
            value = "K";
        }
        return value;
    }  // return "A", "2", ..."Q"

//overloaded operators
    bool operator == (const Card& rhs) const{
        int checkRank = rhs.getRank();
        if (checkRank == myRank && sameSuitAs(rhs)){
            return 1;
        }
        else{
            return 0;
        }
    }
    bool operator != (const Card& rhs) const{
        int checkRank = rhs.getRank();
        if (checkRank == myRank && sameSuitAs(rhs)){
            return 0;
        }
        else{
            return 1;
        }
    }



private:

    int myRank;
    Suit mySuit;


};

ostream& operator << (ostream& out, const Card& c);



#endif