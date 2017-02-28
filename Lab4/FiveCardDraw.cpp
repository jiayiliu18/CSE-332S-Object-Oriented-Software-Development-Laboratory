// FiveCardDraw.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the FiveCardDraw class member functions
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "PokerGame.h"
#include "FiveCardDraw.h"
#include "Deck.h"
#include "Hand.h"
#include "Card.h"
#include "myException.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

enum returnValue1 { noMoreCards = -1, success = 0 };

// constructor:
FiveCardDraw::FiveCardDraw() = default;

// user discards cards
int FiveCardDraw::before_turn(Player &p)
{
	cout << p.username << ": " << p.cards << endl;
	cout << "Give the position of the cards to discard sequentially, the first card is at position 0" << endl;
	cout << "If you finish (no card to discard), type n" << endl;

	char in;
	int i = 0, j = 0; // i is the position the user indicates
	while (cin >> in)
	{
		if (in == 'n')
		{
			break;
		}
		i = in - 48; // change the char value to int
		try
		{
			Card c = p.cards.remove_card(i - j);
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
				sort(p.cards.cards.begin(), p.cards.cards.end());
			}
		}
		else
		{
			discard_deck.shuffling();
			for (int i = 0; i < main; ++i)
			{
				p.cards << main_deck;
				sort(p.cards.cards.begin(), p.cards.cards.end());
			}
			for (int i = 0; i < (num - main); ++i)
			{
				p.cards << discard_deck;
				sort(p.cards.cards.begin(), p.cards.cards.end());
			}
		}
		return success;
	}
}

// display the player's cards after each turn
int FiveCardDraw::after_turn(Player & p)
{
	cout << endl << p.username << ": " << p.cards << endl;
	return success;
}

// a new round
int FiveCardDraw::before_round()
{
	// shuffle the main deck
	main_deck.shuffling();
	// each player should spend a chip to join the round
	for (auto p : players)
	{
		--(p->chips);
	}
	pot = players.size();

	// I increment the dealer here not in the after_round method, but the effect should be the same
	players.push_back(players[0]);
	players.erase(players.begin());

	// deal 5 cards to each player staring at the dealer
	for (int i = 0; i < 5; ++i)
	{
		for (auto p : players)
		{
			p->cards << main_deck;
			sort(p->cards.cards.begin(), p->cards.cards.end());
		}
	}

	// 1st betting phase:
	// reset the records
	numOfFold = 0;
	for (auto p : players)
	{
		p->isFold = false;
		cout << p->username << ": " << p->cards;
	}
	phase();

	// players discard cards staring at the dealer
	if (players.size()-numOfFold >= 2)
	{
		for (auto p : players)
		{
			if (!p->isFold)
			{
				before_turn(*p);
			}	
		}
	}

	return success;
}

int FiveCardDraw::round()
{
	int result = success;
	if (players.size() - numOfFold >= 2)
	{
		for (auto p : players)
		{
			if (!p->isFold)
			{
				result = turn(*p);
				if (result == noMoreCards)
				{
					break;
				}
				cout << p->username << ": " << p->cards;
			}
		}
		phase();
	}
	return result;
}

int FiveCardDraw::after_round()
{
	// sort the players by their hands
	vector<shared_ptr<Player>> sortPlayers;
	for (auto p : players)
	{
		if (!p->isFold) 
		{
			sortPlayers.push_back(p);
		}
	}
	sort(sortPlayers.begin(), sortPlayers.end(), pokerRank2);
	// find out the winner(s)
	size_t w = 1;
	for (size_t j = 1; j < sortPlayers.size(); ++j)
	{
		if (pokerRank2(sortPlayers[0], sortPlayers[j]))
		{
			w = j;
			break;
		}
	}
	// record win and loss
	for (size_t i = 0; i < w; ++i)
	{
		++(sortPlayers[i]->wins);
	}
	for (size_t i = w; i < sortPlayers.size(); ++i)
	{
		++(sortPlayers[i]->losses);
	}
	for (auto p : players)
	{
		if (p->isFold)
		{
			++(p->losses);
		}
	}

	// the winner gets the entire pot
	sortPlayers[0]->chips = sortPlayers[0]->chips + pot;
	pot = 0;

	// display the results
	for (auto i : sortPlayers)
	{
		cout << *i << i->cards << endl;
	}
	for (auto p : players)
	{
		if (p->isFold)
		{
			cout << *p << endl;
		}
	}

	// remove all the cards to the main deck
	for (auto i : players)
	{
		i->cards.cards.clear();
	}
	discard_deck.cards.clear();
	main_deck.cards.clear();
	main_deck.newDeck();
	resetOrLeave();

	// write the files and remove all players
	for (auto p : players)
	{
		string file = p->username + ".txt";
		ofstream out(file.c_str());
		out << p->wins << " " << p->losses << " " << p->chips;
		out.close();
	}
	players.clear();

	return success;
}