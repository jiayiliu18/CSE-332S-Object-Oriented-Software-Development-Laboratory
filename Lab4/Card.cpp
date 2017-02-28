// Card.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Card member functions

#include "stdafx.h"
#include "Card.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// order the cards by rank and then suit
bool Card::operator< (const Card & anotherCard) const
{
	if (r == anotherCard.r)
	{
		return (s < anotherCard.s);
	}
	return (r < anotherCard.r);
}

// determine if two cards are the same
bool Card::operator== (const Card & anotherCard) const
{
	return (r == anotherCard.r && s == anotherCard.s);
}

// The definition of the << operator which prints out a card
ostream & operator<<(ostream & out, const Card & card)
{
	string c;
	switch (card.r)
	{
	case Card::rank::two: c = "2"; break;
	case Card::rank::three: c = "3"; break;
	case Card::rank::four: c = "4"; break;
	case Card::rank::five: c = "5"; break;
	case Card::rank::six: c = "6"; break;
	case Card::rank::seven: c = "7"; break;
	case Card::rank::eight: c = "8"; break;
	case Card::rank::nine: c = "9"; break;
	case Card::rank::ten: c = "10"; break;
	case Card::rank::jack: c = "J"; break;
	case Card::rank::queen: c = "Q"; break;
	case Card::rank::king: c = "K"; break;
	case Card::rank::ace: c = "A"; break;
	}
	switch (card.s)
	{
	case Card::suit::clubs: c += "C"; break;
	case Card::suit::diamonds: c += "D"; break;
	case Card::suit::hearts: c += "H"; break;
	case Card::suit::spades: c += "S"; break;
	}
	out << c << " ";
	return out;
}