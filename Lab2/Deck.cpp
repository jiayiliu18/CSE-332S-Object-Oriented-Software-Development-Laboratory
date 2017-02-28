// Deck.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu
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

// constructor
Deck::Deck(char *fname)
{
	bool isLoad = load(fname);
	if (!isLoad)
	{
		throw runtime_error("Cannot open the file.");
	}
}

// loads the given file and read in valid card strings to the member variable
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

// shuffles the cards in the deck
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