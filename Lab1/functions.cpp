// functions.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu
// This file contains all the function definitions

#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// lists the return values and their meanings
enum returnVal { missFileName = -1, success = 0, invalidFileName = 1, invalidFileContent = 2 };

// This is the file parsing function
// which reads in a line(a hand) from the file at a time 
// and stores valid hands(5 cards per hand) into a vector of Card
int parsing(vector<Card> &cards, char *fname)
{
	const int minStringSize = 2;	// the min length of the card definition string
	const int maxStringSize = 3;	// the max length of the card definition string
	const int first = 0;			// 1st char of the card definition string
	const int second = 1;			// 2nd char of the card definition string
	const int third = 2;			// 3rd char of the card definition string
	const int num_card = 5;			// the number of cards in a hand

	ifstream ifs(fname);
	string line, c; // hold a line and each word in the line, respectively

	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			istringstream iss(line);
			vector<Card> hand; // holds a hand from the line

			while ((iss >> c) && (c != "//"))
			{
				Card card; // holds each card in the hand

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
						case '2': card.r = Card::rank::two; hand.push_back(card); break;
						case '3': card.r = Card::rank::three; hand.push_back(card); break;
						case '4': card.r = Card::rank::four; hand.push_back(card); break;
						case '5': card.r = Card::rank::five; hand.push_back(card); break;
						case '6': card.r = Card::rank::six; hand.push_back(card); break;
						case '7': card.r = Card::rank::seven; hand.push_back(card); break;
						case '8': card.r = Card::rank::eight; hand.push_back(card); break;
						case '9': card.r = Card::rank::nine; hand.push_back(card); break;
						case 'J': case 'j': card.r = Card::rank::jack; hand.push_back(card); break;
						case 'Q': case 'q': card.r = Card::rank::queen; hand.push_back(card); break;
						case 'K': case 'k': card.r = Card::rank::king; hand.push_back(card); break;
						case 'A': case 'a': card.r = Card::rank::ace; hand.push_back(card); break;
						default: cerr << "Invalid card: " << c << endl; break;
						}
					}

					else
					{
						cerr << "Invalid card: " << c << endl;
					}
				}

				else if (c.size() == maxStringSize)
				{
					if (c[first] == '1' && c[second] == '0')
					{
						card.r = Card::rank::ten;

						switch (c[third])
						{
						case 'C': case 'c': card.s = Card::suit::clubs; hand.push_back(card); break;
						case 'D': case 'd': card.s = Card::suit::diamonds; hand.push_back(card); break;
						case 'H': case 'h': card.s = Card::suit::hearts; hand.push_back(card); break;
						case 'S': case 's': card.s = Card::suit::spades; hand.push_back(card); break;
						default: cerr << "Invalid card: " << c << endl; break;
						}
					}

					else
					{
						cerr << "Invalid card: " << c << endl;
					}
				}

				// If the card definition string is not 2 or 3 char long
				else
				{
					cerr << "Invalid card: " << c << endl;
				}			
			}

			// now check if there are exactly 5 cards in the hand
			// if it is, copy the 5 cards into the cards vector
			if (hand.size() == num_card)
			{
				for (auto i : hand)
				{
					cards.push_back(i);
				}
			}

			// if there are more or fewer than five cards in a line, print out a warning
			// Notice: skip blank lines
			else if (hand.size() > 0 && hand.size() < num_card || hand.size() > num_card)
			{
				cerr << "Not five cards in the hand!" << endl;
			}
		}

		ifs.close();
		return success;
	}

	// if the name of the file is invalid; or the file doesn't exist
	else
	{
		cerr << "Fail to open the file." << endl;
		return invalidFileName;
	}
}


// This function prints out valid cards
int printing(const vector<Card> &cards)
{
	const int minCardNum = 1;

	// when the file contains valid card strings
	if (cards.size() >= minCardNum)
	{
		string c;
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

			cout << c << endl;
		}
		return success;
	}

	// when there's no card to print
	else
	{
		cerr << "There's no card to print." << endl;
		return invalidFileContent;
	}
}


// This function determines the rank of each hand in the card vector
int ranking(const vector<Card> &cards)
{
	const int num_card = 5;
	// check if there are cards to proceed
	if (cards.size() >= num_card)
	{
		vector<Card> rankedCards = cards; // stores sorted cards in each hand
		string handRank;

		for (size_t i = 0; i < (rankedCards.size() - 4); i = i + num_card)
		{
			// sort the five cards in the current hand
			sort(rankedCards.begin() + i, rankedCards.begin() + i + num_card);

			// determine the rank of this hand
			if (rankedCards[i].s == rankedCards[i + 1].s && rankedCards[i].s == rankedCards[i + 2].s && rankedCards[i].s == rankedCards[i + 3].s && rankedCards[i].s == rankedCards[i + 4].s)
			{
				if (rankedCards[i].r == rankedCards[i + 1].r - 1 && rankedCards[i].r == rankedCards[i + 2].r - 2 && rankedCards[i].r == rankedCards[i + 3].r - 3 && rankedCards[i].r == rankedCards[i + 4].r - 4)
				{
					handRank = "straight flush";
				}
				else
				{
					handRank = "flush";
				}
			}
			else
			{
				if (rankedCards[i].r == rankedCards[i + 1].r - 1 && rankedCards[i].r == rankedCards[i + 2].r - 2 && rankedCards[i].r == rankedCards[i + 3].r - 3 && rankedCards[i].r == rankedCards[i + 4].r - 4)
				{
					handRank = "straight";
				}
				else if (rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i].r == rankedCards[i + 2].r && rankedCards[i].r == rankedCards[i + 3].r || rankedCards[i + 1].r == rankedCards[i + 2].r && rankedCards[i + 1].r == rankedCards[i + 3].r && rankedCards[i + 1].r == rankedCards[i + 4].r)
				{
					handRank = "four of a kind";
				}
				else if (rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i].r == rankedCards[i + 2].r && rankedCards[i + 3].r == rankedCards[i + 4].r || rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i + 2].r == rankedCards[i + 3].r && rankedCards[i + 2].r == rankedCards[i + 4].r)
				{
					handRank = "full house";
				}
				else if (rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i].r == rankedCards[i + 2].r || rankedCards[i + 1].r == rankedCards[i + 2].r && rankedCards[i + 1].r == rankedCards[i + 3].r || rankedCards[i + 2].r == rankedCards[i + 3].r && rankedCards[i + 2].r == rankedCards[i + 4].r)
				{
					handRank = "three of a kind";
				}
				else if (rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i + 2].r == rankedCards[i + 3].r || rankedCards[i + 1].r == rankedCards[i + 2].r && rankedCards[i + 3].r == rankedCards[i + 4].r || rankedCards[i].r == rankedCards[i + 1].r && rankedCards[i + 3].r == rankedCards[i + 4].r)
				{
					handRank = "two pairs";
				}
				else if (rankedCards[i].r == rankedCards[i + 1].r || rankedCards[i + 1].r == rankedCards[i + 2].r || rankedCards[i + 2].r == rankedCards[i + 3].r || rankedCards[i + 3].r == rankedCards[i + 4].r)
				{
					handRank = "one pair";
				}
				else
				{
					handRank = "no rank";
				}
			}

			cout << handRank << endl;
		}
		
		return success;		
	}

	else
	{
		return invalidFileContent;
	}
}


// This function tells how to use the program correctly
int usage(char *pname)
{
	cout << "Purpose: This program reads and parses some card definition strings from a text file." << endl
		<< "Usage: Enter the file's name after the program's name, like " << endl
		<< pname << " card_file.txt" << endl;
	return missFileName;
}