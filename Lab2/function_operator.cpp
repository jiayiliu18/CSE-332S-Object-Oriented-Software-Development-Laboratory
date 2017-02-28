// function_operator.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu
// Definitions of the non-member operators and functions of the Deck and hand classes

#include "stdafx.h"
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

// The definition of the << operator which prints out each card in the hand 
ostream & operator<<(ostream & out, const Hand & hand)
{
	string result = "";
	string c;
	vector<Card> cards = hand.cards;
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
	out << result << endl;
	return out;
}

// The definition of the << operator which deal a card from deck to hand
void operator<<(Hand & hand, Deck & deck)
{
	Card c = deck.cards[deck.cards.size() - 1];
	deck.cards.pop_back();
	hand.cards.push_back(c);
	sort(hand.cards.begin(), hand.cards.end());
}

// The definition of the pokerRank function which returns true if the first hand is higher than the second.
// This function also calls another ranking function which gives the rank group of each hand.
// Then if the two hands have different rank groups, it's easy to compare.
// The pokerRank does further comparison if the hands have same rank group.
enum ranks { no_rank, one_pair, two_pairs, three_of_a_kind, straight, flush_, full_house, four_of_a_kind, straight_flush };
bool pokerRank(const Hand & h1, const Hand & h2)
{
	int rank1 = ranking(h1);
	int rank2 = ranking(h2);
	enum index {bgn, first, sec, thd, last};
	int numOfCards = 5;

	if (rank1 == rank2)
	{
		if (rank1 == straight || rank1 == straight_flush)
		{
			return (h2 < h1);
		}

		else if (rank1 == no_rank || rank1 == flush_)
		{
			if (h1.cards[last].r == h2.cards[last].r)
			{
				if (h1.cards[thd].r == h2.cards[thd].r)
				{
						if (h1.cards[sec].r == h2.cards[sec].r)
						{
							if (h1.cards[first].r == h2.cards[first].r)
							{
								return (h2.cards[bgn].r < h1.cards[bgn].r);
							}
							else
							{
								return (h1.cards[first].r > h2.cards[first].r);
							}
						}
						else
						{
							return (h1.cards[sec].r > h2.cards[sec].r);
						}
				}
				else
				{
					return (h1.cards[thd].r > h2.cards[thd].r);
				}
			}
			else 
			{
				return (h1.cards[last].r > h2.cards[last].r);
			}
		}

		else if (rank1 == four_of_a_kind)
		{
			return (h2.cards[3] < h1.cards[3]);
		}
		else if (rank1 == full_house || rank1 == three_of_a_kind)
		{
			return (h2.cards[2] < h1.cards[2]);
		}
		else if (rank1 == two_pairs)
		{
			if (h2.cards[thd].r == h1.cards[thd].r)
			{
				if (h2.cards[first].r == h1.cards[first].r)
				{
					if (h2.cards[sec].r == h1.cards[sec].r)
					{
						if (h2.cards[bgn].r == h1.cards[bgn].r)
						{
							return (h2.cards[last].r < h1.cards[last].r);
						}
						else
						{
							return (h2.cards[bgn].r < h1.cards[bgn].r);
						}
					}
					else
					{
						return (h2.cards[sec].r < h1.cards[sec].r);
					}
				}
				else
				{
					return (h2.cards[first].r < h1.cards[first].r);
				}
			}
			else
			{
				return (h2.cards[thd].r < h1.cards[thd].r);
			}			
		}
		else  // one_pair
		{
			int cnt = 0;
			int index1 = 0;
			int index2 = 0;
			// stores the rank of each card in h1
			vector<Card::rank> r1;
			for (int i = 0; i < numOfCards; ++i)
			{
				r1.push_back(h1.cards[i].r);
			}
			// stores the rank of each card in h1
			vector<Card::rank> r2;
			for (int i = 0; i < numOfCards; ++i)
			{
				r2.push_back(h2.cards[i].r);
			}

			for (int i = 0; i < numOfCards; ++i)
			{
				cnt = count(r1.begin(), r1.end(), r1[i]);
				if (cnt == 2)
				{
					index1 = i;
					break;
				}
			}
			for (int i = 0; i < numOfCards; ++i)
			{
				cnt = count(r2.begin(), r2.end(), r2[i]);
				if (cnt == 2)
				{
					index2 = i;
					break;
				}
			}
			if (h2.cards[index2].r == h1.cards[index1].r)
			{
				if (h1.cards[last].r == h2.cards[last].r)
				{
					if (h1.cards[thd].r == h2.cards[thd].r)
					{
						if (h1.cards[sec].r == h2.cards[sec].r)
						{
							if (h1.cards[first].r == h2.cards[first].r)
							{
								return (h2.cards[bgn].r < h1.cards[bgn].r);
							}
							else
							{
								return (h1.cards[first].r > h2.cards[first].r);
							}
						}
						else
						{
							return (h1.cards[sec].r > h2.cards[sec].r);
						}
					}
					else
					{
						return (h1.cards[thd].r > h2.cards[thd].r);
					}
				}
				else
				{
					return (h1.cards[last].r > h2.cards[last].r);
				}
			}
			else
			{
				return (h2.cards[index2].r < h1.cards[index1].r);
			}
			
		}
	}
	else
	{
		return (rank1 > rank2);
	}
}

// The definition of the ranking function which returns a hand's rank group as an integer.
int ranking(const Hand & h)
{
	int handRank = 0;
	if (h.cards[0].s == h.cards[1].s && h.cards[0].s == h.cards[2].s && h.cards[0].s == h.cards[3].s && h.cards[0].s == h.cards[4].s)
	{
			if (h.cards[0].r == h.cards[1].r - 1 && h.cards[0].r == h.cards[2].r - 2 && h.cards[0].r == h.cards[3].r - 3 && h.cards[0].r == h.cards[4].r - 4)
			{
				handRank = straight_flush;
			}
			else
			{
				handRank = flush_;
			}
	}
	else
	{
			if (h.cards[0].r == h.cards[1].r - 1 && h.cards[0].r == h.cards[2].r - 2 && h.cards[0].r == h.cards[3].r - 3 && h.cards[0].r == h.cards[4].r - 4)
			{
				handRank = straight;
			}
			else if (h.cards[0].r == h.cards[1].r && h.cards[0].r == h.cards[2].r && h.cards[0].r == h.cards[3].r || h.cards[1].r == h.cards[2].r && h.cards[1].r == h.cards[3].r && h.cards[1].r == h.cards[4].r)
			{
				handRank = four_of_a_kind;
			}
			else if (h.cards[0].r == h.cards[1].r && h.cards[0].r == h.cards[2].r && h.cards[3].r == h.cards[4].r || h.cards[0].r == h.cards[1].r && h.cards[2].r == h.cards[3].r && h.cards[2].r == h.cards[4].r)
			{
				handRank = full_house;
			}
			else if (h.cards[0].r == h.cards[1].r && h.cards[0].r == h.cards[2].r || h.cards[1].r == h.cards[2].r && h.cards[1].r == h.cards[3].r || h.cards[2].r == h.cards[3].r && h.cards[2].r == h.cards[4].r)
			{
				handRank = three_of_a_kind;
			}
			else if (h.cards[0].r == h.cards[1].r && h.cards[2].r == h.cards[3].r || h.cards[1].r == h.cards[2].r && h.cards[3].r == h.cards[4].r || h.cards[0].r == h.cards[1].r && h.cards[3].r == h.cards[4].r)
			{
				handRank = two_pairs;
			}
			else if (h.cards[0].r == h.cards[1].r || h.cards[1].r == h.cards[2].r || h.cards[2].r == h.cards[3].r || h.cards[3].r == h.cards[4].r)
			{
				handRank = one_pair;
			}
			else
			{
				handRank = no_rank;
			}
	}
	return handRank;
}

enum returnVal {success = 0, tooMuchArg = 1, oneButShuffle = 2, twoWithoutShuffle = 3, tooFewArg = 4};
// The definition of the usage function which tells how to use the program correctly
int usage(char *pname, char *index)
{
	cout << "This program reads and parses some card definition strings from a text file." << endl
		<< "You can enter the file's name after the program's name, and tpye -shuffle if you want to shuffle cards." << endl
		<< "Example:" << endl
		<< pname << " card_file.txt" << endl
		<< "Or:" << endl
		<< pname << " card_file.txt -shuffle" << endl;

	if (index == "tooMuchArg")
	{
		return tooMuchArg;
	}
	else if (index == "oneButShuffle")
	{
		return oneButShuffle;
	}
	else if (index == "twoWithoutShuffle")
	{
		return twoWithoutShuffle;
	}
	else {  //"tooFewArg"
		return tooFewArg;
	}
}