// Card.h
// Author: Jennie Liu    jiayiliu@wustl.edu
// Declaration and definition of the card class

#pragma once
#ifndef CARD_H
#define CARD_H
#include <vector>

struct Card
{
	enum suit { clubs, diamonds, hearts, spades };
	enum rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
	suit s;
	rank r;

	// the less than operator to order the cards by rank and suit
	bool operator< (const Card & anotherCard) const;

	// the equivalence operator to determine if two cards are the same
	bool operator== (const Card & anotherCard) const;
};
#endif // !CARD_H