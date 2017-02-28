// FiveCardDraw.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the FiveCardDraw class member functions
// Definitions of the non-member functions
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "Deck.h"
#include "Hand.h"
#include "Card.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

enum returnV { noMoreCards = -1, success = 0, tooFewArg = 1 };

// constructor:
FiveCardDraw::FiveCardDraw()
{
	Card c;
	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case 0: c.s = Card::suit::clubs; break;
		case 1: c.s = Card::suit::diamonds; break;
		case 2: c.s = Card::suit::hearts; break;
		case 3: c.s = Card::suit::spades; break;
		}
		for (int j = 0; j < 13; ++j)
		{
			switch (j)
			{
			case 0: c.r = Card::rank::two; break;
			case 1: c.r = Card::rank::three; break;
			case 2: c.r = Card::rank::four; break;
			case 3: c.r = Card::rank::five; break;
			case 4: c.r = Card::rank::six; break;
			case 5: c.r = Card::rank::seven; break;
			case 6: c.r = Card::rank::eight; break;
			case 7: c.r = Card::rank::nine; break;
			case 8: c.r = Card::rank::ten; break;
			case 9: c.r = Card::rank::jack; break;
			case 10: c.r = Card::rank::queen; break;
			case 11: c.r = Card::rank::king; break;
			case 12: c.r = Card::rank::ace; break;
			}
			main_deck.add_card(c);
		}
	}
}

// the virtuals:
// user discards cards
int FiveCardDraw::before_turn(Player &p)
{
	cout << endl;
	cout << p.username << ":" << endl << p.cards << endl;
	cout << "Enter the position of the cards to discard sequentially, starting at 0" << endl;
	cout << "If you finish, enter n" << endl;
	cout << "If no card to discard, enter n" << endl;

	char in;
	int i = 0, j = 0;
	while (cin >> in)
	{
		if (in == 'n')
		{
			break;
		}
		i = in - 48;
		try
		{
			Card c = p.cards.remove_card(i-j);
			discard_deck.add_card(c);		
			++j; // Here is very tricky! remove_card method uses erase and invalidate the following index.
		}
		catch (out_of_range err)
		{
			cout << err.what() << " Try again." << endl;
		}
	}
	return success;
}

// deal cards to let the player have five cards in hand
int FiveCardDraw::turn(Player &p)
{
	// the number of cards needed
	int num = 5 - p.cards.size();
	// the number of cards in the main deck
	int main = main_deck.size();
	// the number of cards in the discard deck
	int discard = discard_deck.size();
	if (num > (main + discard))
	{
		return noMoreCards;
	}
	else
	{
		if (main >= num)
		{
			for (int i = 0; i < num; ++i)
			{
				p.cards << main_deck;
			}
		}
		else
		{
			discard_deck.shuffling();
			for (int i = 0; i < main; ++i)
			{
				p.cards << main_deck;
			}
			for (int i = 0; i < (num - main); ++i)
			{
				p.cards << discard_deck;
			}
		}
		return success;
	}
}

// display the player's cards after one turn
int FiveCardDraw::after_turn(Player & p)
{
	cout << endl << p.username << ":" << endl << p.cards << endl;
	return success;
}

// a new round
// I increment the dealer here not in the after_round method, but the effect should be the same
int FiveCardDraw::before_round()
{
	main_deck.shuffling();
	if (dealer == (players.size() - 1))
	{
		dealer = 0;
	}
	else
	{
		++dealer;
	}
	for (int i = 0; i < 5; ++i)
	{

		for (size_t j = dealer; j < players.size(); ++j)
		{
			players[j]->cards << main_deck;
		}
		for (size_t j = 0; j < dealer; ++j)
		{
			players[j]->cards << main_deck;
		}		
	}
	
	for (size_t j = dealer; j < players.size(); ++j)
	{
		before_turn(*players[j]);
	}
	for (size_t j = 0; j < dealer; ++j)
	{
		before_turn(*players[j]);
	}
	return success;
}

int FiveCardDraw::round()
{
	int result = success;
	for (size_t j = dealer; j < players.size(); ++j)
	{
		result = turn(*players[j]);
		if (result == noMoreCards)
		{
			break;
		}
		after_turn(*players[j]);
	}
	for (size_t j = 0; j < dealer; ++j)
	{
		result = turn(*players[j]);
		if (result == noMoreCards)
		{
			break;
		}
		after_turn(*players[j]);
	}
	return result;
}

int FiveCardDraw::after_round()
{
	// sort the players
	vector<shared_ptr<Player>> sortPlayers(players);
	sort(sortPlayers.begin(),sortPlayers.end(),pokerRank2);

	size_t w;
	for (size_t j = 1; j < sortPlayers.size(); ++j)
	{
		if (pokerRank2(sortPlayers[0], sortPlayers[j]))
		{
			w = j;
			break;
		}
	}
	for (size_t i = 0; i < w; ++i)
	{
		sortPlayers[i]->wins = sortPlayers[i]->wins + 1;
	}
	for (size_t i = w; i < sortPlayers.size(); ++i)
	{
		sortPlayers[i]->losses = sortPlayers[i]->losses + 1;
	}

	for (auto i : sortPlayers)
	{
		cout << i->username << endl << "number of wins: " << i->wins << " number of losses: " << i->losses << endl;
		cout << i->cards << endl;
	}

	// remove all the cards to the main deck
	for (auto i : players)
	{
		i->cards.cards.clear();
	}
	discard_deck.cards.clear();
	main_deck.cards.clear();
	Card c;
	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case 0: c.s = Card::suit::clubs; break;
		case 1: c.s = Card::suit::diamonds; break;
		case 2: c.s = Card::suit::hearts; break;
		case 3: c.s = Card::suit::spades; break;
		}
		for (int j = 0; j < 13; ++j)
		{
			switch (j)
			{
			case 0: c.r = Card::rank::two; break;
			case 1: c.r = Card::rank::three; break;
			case 2: c.r = Card::rank::four; break;
			case 3: c.r = Card::rank::five; break;
			case 4: c.r = Card::rank::six; break;
			case 5: c.r = Card::rank::seven; break;
			case 6: c.r = Card::rank::eight; break;
			case 7: c.r = Card::rank::nine; break;
			case 8: c.r = Card::rank::ten; break;
			case 9: c.r = Card::rank::jack; break;
			case 10: c.r = Card::rank::queen; break;
			case 11: c.r = Card::rank::king; break;
			case 12: c.r = Card::rank::ace; break;
			}
			main_deck.add_card(c);
		}
	}

	// ask whether to leave the game
	for (size_t i = 0; i < players.size(); ++i)
	{
		cout << "Do you want to leave? If so, type your name, otherwise type no" << endl;
		string resp;
		cin >> resp;
		if (resp != "no")
		{
			for (size_t j = 0; j < players.size(); ++j)
			{
				// find the player
				if ((players[j]->username) == resp)
				{
					string file = resp + ".txt";
					ofstream out(file.c_str());
					out << players[j]->wins << " " << players[j]->losses;
					out.close();
					players.erase(players.begin()+j);
					--j; --i;
				}
			}
		}
	}
	// ask whether to join the game
	for (size_t i = 0; i < players.size(); ++i)
	{
		cout << "Do you want to join? If so, type your name, otherwise type no" << endl;
		string resp;
		cin >> resp;
		if (resp != "no")
		{
			try
			{
				add_player(resp);
			}
			catch(runtime_error err)
			{
				cout << err.what() << endl;
			}
		}
	}
	return success;
}

bool pokerRank2(shared_ptr<Player> p1, shared_ptr<Player> p2)
{
	if (p1 == nullptr)
	{
		return false;
	}
	else
	{
		if (p2 == nullptr)
		{
			return true;
		}
		else
		{
			return pokerRank1(p1->cards,p2->cards);
		}
	}
}

// The definition of the pokerRank function which returns true if the first hand is higher than the second.
// This function also calls another ranking function which gives the rank group of each hand.
enum ranks { no_rank, one_pair, two_pairs, three_of_a_kind, straight, flush_, full_house, four_of_a_kind, straight_flush };
bool pokerRank1(const Hand & h1, const Hand & h2)
{
	int rank1 = ranking(h1);
	int rank2 = ranking(h2);
	enum index { bgn, first, sec, thd, last };
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

// The definition of the usage function which tells how to use the program correctly
int usage(char *index)
{
	cout << "This program supports the five card draw game." << endl
		<< "Enter the game name FiveCardDraw followed by the names of the player." << endl
		<< "There should be at least two players to start the game." << endl
		<< "And the name of the players should be only one word starting with a letter." << endl;

		return tooFewArg;
}