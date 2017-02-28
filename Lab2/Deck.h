// Deck.h
// Author: Jennie Liu    jiayiliu@wustl.edu
// Declaration and definition of the Deck class and declaration of its non-member operators

#pragma once
#ifndef DECK_H
#define DECK_H
#include <vector>
#include <iostream>
#include "Card.h"
#include "Hand.h"
using namespace std;

class Hand;  // This is very important to make the << operator which takes both a hand and a deck to work!

class Deck
{
	// the non-member insertion operators which need to access Deck's member variable
	friend ostream & operator<<(ostream & out, const Deck & deck);
	friend void operator<<(Hand & hand, Deck & deck);

	public:
		// constructor
		Deck(char *fname);

		// Here I think the destructor is not required to be declared and defined explicitly,
		// since we don't acquire any resources in the constructor, 
		// and we don't either have a copy constructor or a copy assignment operator declared explicitly.

		// loads the given file and read in valid card strings to the member variable
		// returns true on successful loading and false on in valid filename
		bool load(char *fname);

		// shuffles the cards in the deck
		void shuffling();

		// returns the number of cards in the deck
		int size() const;
	
	private:
		// the member variable:
		vector<Card> cards;		
};

// The declaration of the insertion operator <<
ostream & operator<<(ostream & out, const Deck & deck);
#endif