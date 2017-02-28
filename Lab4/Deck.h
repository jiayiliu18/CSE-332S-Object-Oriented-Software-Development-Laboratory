// Deck.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Deck class and declaration of its non-member operators

#pragma once
#ifndef DECK_H
#define DECK_H
#include <vector>
#include <iostream>
#include "Card.h"
#include "Hand.h"
using namespace std;

class Hand;
class FiveCardDraw;
class SevenCardStud;

class Deck
{
	// the non-member insertion operators which need access to Deck's member variable
	friend std::ostream & operator<<(std::ostream & out, const Deck & deck);
	friend void operator<<(Hand & hand, Deck & deck);
	friend class FiveCardDraw;
	friend class SevenCardStud;

public:
	// default constructor
	Deck();

	// another constructor that reads cards from a file
	Deck(char *fname);

	// load the given file and read in valid card strings
	// returns true on successful loading and false on invalid filename
	bool load(char *fname);

	// shuffle the cards in the deck
	void shuffling();

	// returns the number of cards in the deck
	int size() const;

	// add a card to the deck
	void add_card(Card c);

	// construct a new deck with 52 cards
	void newDeck();

private:
	// member variable:
	std::vector<Card> cards;
};

// declaration of the insertion operator <<
std::ostream & operator<<(std::ostream & out, const Deck & deck);
#endif