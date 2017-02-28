// Hand.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu
// Definition of the Hand class member functions

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// default constructor
Hand::Hand() = default;

// copy constructor
Hand::Hand(const Hand & anotherHand)
{
	cards = anotherHand.cards;
}

// destructor
Hand::~Hand() = default;

// assignment operator
Hand & Hand::operator= (const Hand & anotherHand)
{
	if (cards != anotherHand.cards)
	{
		cards = anotherHand.cards;
	}
	return *this;
}

// returns the number of cards in the hand
int Hand::size() const
{
	return cards.size();
}

// equivalence operator
bool Hand::operator== (const Hand & anotherHand) const
{
	return (cards == anotherHand.cards);
}

// less than operator
bool Hand::operator< (const Hand & anotherHand) const
{
	bool returnValue = true;
	for (size_t i = 0; i < cards.size(); ++i)
	{
		if (anotherHand.cards.size() > i)
		{
			if (cards[i] < anotherHand.cards[i])
			{
				returnValue = true;
				break;
			}
			else if (anotherHand.cards[i] < cards[i])
			{
				returnValue = false;
				break;
			}
		}
		else
		{
			returnValue = false;
			break;
		}
	}
	if (cards == anotherHand.cards)
	{
		returnValue = false;
	}
	return returnValue;
}

// returns a string containing the cards in the member variable
string Hand::asString() const
{
	string result = "";   // cards in the member variable
	string c;   // a single card
	for (size_t i = 0; i < cards.size(); ++i)
	{
		switch (cards[i].r)
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
		switch (cards[i].s)
		{
		case Card::suit::clubs: c += "C"; break;
		case Card::suit::diamonds: c += "D"; break;
		case Card::suit::hearts: c += "H"; break;
		case Card::suit::spades: c += "S"; break;
		}
		result = result + c + " ";
	}
	return result;
}