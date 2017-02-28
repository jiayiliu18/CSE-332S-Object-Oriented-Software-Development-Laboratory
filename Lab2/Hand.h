// Hand.h
// Author: Jennie Liu    jiayiliu@wustl.edu
// Declaration and definition of the Hand class and declaration of its non-member operators 
// Declaration of the pokerRank function and the usage function

#pragma once
#ifndef HAND_H
#define HAND_H
#include <vector>
#include <string>
#include <iostream>
#include "Card.h"
#include "Deck.h"
using namespace std;

class Deck; // This is very important to make the << operator which takes both a hand and a deck to work!

class Hand
{
	// the non-member insertion operator which need to access Hand's member variable
	friend ostream & operator<<(ostream & out, const Hand & hand);
	friend void operator<<(Hand & hand, Deck & deck);
	// the non-member functions which need to access Hand's member variable
	friend bool pokerRank(const Hand & h1, const Hand & h2);
	friend int ranking(const Hand & h);

	public:	
		// default constructor
		Hand (); 

		// copy constructor
		Hand(const Hand &);

		// destructor
		virtual ~Hand();

		// assignment operator
		Hand & operator= (const Hand &);

		// returns the number of cards in the hand
		int size() const;

		// equivalence operator
		bool operator== (const Hand &) const;

		// less than operator
		bool operator< (const Hand &) const;

		// returns a string containing the cards in the member variable
		string asString() const;

	private:
		// the member variable:
		vector<Card> cards;
};

// Declaration of the insertion operator <<
ostream & operator<<(ostream & out, const Hand & hand);
void operator<<(Hand & hand, Deck & deck);

// Declaration of the pokerRank function which calls another function (ranking).
bool pokerRank(const Hand & h1, const Hand & h2);
int ranking(const Hand & h);

// Declaration of the usage function which tells how to use the program correctly
int usage(char *pname, char *index);
#endif