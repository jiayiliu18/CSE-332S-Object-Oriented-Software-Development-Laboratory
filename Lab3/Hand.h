// Hand.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Hand class and declaration of its non-member operators 

#pragma once
#ifndef HAND_H
#define HAND_H
#include <vector>
#include <string>
#include <iostream>
#include "Card.h"
#include "Deck.h"

class Deck; 
class FiveCardDraw;

class Hand
{
	// the non-member operators and functions which need access to Hand's member variable
	friend std::ostream & operator<<(std::ostream & out, const Hand & hand);
	friend void operator<<(Hand & hand, Deck & deck);
	friend bool pokerRank1(const Hand & h1, const Hand & h2);
	friend int ranking(const Hand & h);
	friend class FiveCardDraw;

public:
	// default constructor
	Hand();

	// copy constructor
	Hand(const Hand &);

	// destructor
	~Hand();

	// assignment operator
	Hand & operator= (const Hand &);

	// returns the number of cards in the hand
	int size() const;

	// equivalence operator
	bool operator== (const Hand &) const;

	// less than operator
	bool operator< (const Hand &) const;

	// returns a string containing the cards in the member variable
	std::string asString() const;

	// indexing operator
	Card & operator[](size_t n);
	const Card & operator[](size_t n) const;

	// remove the card at position n and return the removed card
	Card remove_card(size_t n);

private:
	// the member variable:
	std::vector<Card> cards;
};

std::ostream & operator<<(std::ostream & out, const Hand & hand);
void operator<<(Hand & hand, Deck & deck);
#endif