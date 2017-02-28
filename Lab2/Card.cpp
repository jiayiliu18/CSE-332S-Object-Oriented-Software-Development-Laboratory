// Card.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu
// Definition of the Deck class member functions

#include "stdafx.h"
#include "Card.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// the less than operator to order the cards by rank and suit
bool Card::operator< (const Card & anotherCard) const
{
	if (r == anotherCard.r)
	{
		return (s < anotherCard.s);
	}
	return (r < anotherCard.r);
}

// the equivalence operator to determine if two cards are the same
bool Card::operator== (const Card & anotherCard) const
{
	return (r == anotherCard.r && s == anotherCard.s);
}