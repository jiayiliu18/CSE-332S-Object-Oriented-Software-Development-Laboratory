// Deck.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Deck class member functions

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <random>
using namespace std;

// default constructor
Deck::Deck() = default;

// another constructor that reads cards from a file
Deck::Deck(char *fname)
{
	bool isLoad = load(fname);
	if (!isLoad)
	{
		throw runtime_error("Cannot open the file.");
	}
}

// load the given file and read in valid card strings
// returns true on successful loading and false on in valid filename
bool Deck::load(char *fname)
{
	const int minStringSize = 2;
	const int maxStringSize = 3;
	const int first = 0;
	const int second = 1;
	const int third = 2;
	ifstream ifs(fname);
	string c;
	Card card;
	if (ifs.is_open())
	{
		while (ifs >> c)
		{
			if (c.size() == minStringSize)
			{
				if (c[second] == 'C' || c[second] == 'c' || c[second] == 'H' || c[second] == 'h' || c[second] == 'S' || c[second] == 's' || c[second] == 'D' || c[second] == 'd')
				{
					switch (c[second])
					{
					case 'C': case 'c': card.s = Card::suit::clubs; break;
					case 'D': case 'd': card.s = Card::suit::diamonds; break;
					case 'H': case 'h': card.s = Card::suit::hearts; break;
					case 'S': case 's': card.s = Card::suit::spades; break;
					}
					switch (c[first])
					{
					case '2': card.r = Card::rank::two; cards.push_back(card); break;
					case '3': card.r = Card::rank::three; cards.push_back(card); break;
					case '4': card.r = Card::rank::four; cards.push_back(card); break;
					case '5': card.r = Card::rank::five; cards.push_back(card); break;
					case '6': card.r = Card::rank::six; cards.push_back(card); break;
					case '7': card.r = Card::rank::seven; cards.push_back(card); break;
					case '8': card.r = Card::rank::eight; cards.push_back(card); break;
					case '9': card.r = Card::rank::nine; cards.push_back(card); break;
					case 'J': case 'j': card.r = Card::rank::jack; cards.push_back(card); break;
					case 'Q': case 'q': card.r = Card::rank::queen; cards.push_back(card); break;
					case 'K': case 'k': card.r = Card::rank::king; cards.push_back(card); break;
					case 'A': case 'a': card.r = Card::rank::ace; cards.push_back(card); break;
					}
				}
			}
			else if (c.size() == maxStringSize)
			{
				if (c[first] == '1' && c[second] == '0')
				{
					card.r = Card::rank::ten;
					switch (c[third])
					{
					case 'C': case 'c': card.s = Card::suit::clubs; cards.push_back(card); break;
					case 'D': case 'd': card.s = Card::suit::diamonds; cards.push_back(card); break;
					case 'H': case 'h': card.s = Card::suit::hearts; cards.push_back(card); break;
					case 'S': case 's': card.s = Card::suit::spades; cards.push_back(card); break;
					}
				}
			}
			// if the card definition string is not 2 or 3 char long, skip it
			else {}
		}
		ifs.close();
		return true;
	}
	// if the name of the file is invalid; or the file doesn't exist
	else
	{
		return false;
	}
}

// shuffle the cards in the deck
void Deck::shuffling()
{
	random_device rd;
	mt19937 g(rd());
	shuffle(cards.begin(), cards.end(), g);
}

// returns the number of cards in the deck
int Deck::size() const
{
	return cards.size();
}

// add a card to the deck
void Deck::add_card(Card c) 
{
	cards.push_back(c);
}

// The definition of the << operator which prints out each card in the deck 
ostream & operator<<(ostream & out, const Deck & deck)
{
	string c;
	vector<Card> cards = deck.cards;
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
		out << c << endl;
	}
	return out;
}