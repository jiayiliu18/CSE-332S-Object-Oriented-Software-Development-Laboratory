// Card.h
// Author: Jennie Liu    jiayiliu@wustl.edu
// Declarations for a file reading and parsing program, which reads files of card definition strings and outputs their hand ranks and cards in order.

#pragma once
#ifndef CARD_H
#define CARD_H
#include <vector>

// type Card, which has varible members suit and rank, and a < operator
struct Card
{
	enum suit { clubs, diamonds, hearts, spades };
	enum rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
	suit s;
	rank r;

	// Declare and define the less than operator to order the cards by rank and suit
	bool operator< (const Card & anotherCard) const 
	{
		if (r == anotherCard.r)
		{
			return (s < anotherCard.s);
		}
		return (r < anotherCard.r);
	}
};

// function declarations
int parsing(std::vector<Card> &cards, char *fname);
int printing(const std::vector<Card> &cards);
int usage(char *pname);
int ranking(const std::vector<Card> &cards);

#endif // !CARD_H
#pragma once
