// SevenCardStud.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the SevenCardStud class member functions
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "PokerGame.h"
#include "SevenCardStud.h"
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

enum returnValue2 { noMoreCards = -1, success = 0 };

// constructor:
SevenCardStud::SevenCardStud() = default;

int SevenCardStud::before_turn(Player &p)
{
	return success;
}

int SevenCardStud::turn(Player &p)
{
	if (main_deck.size() > 0)
	{
		p.cards << main_deck;
		return success;
	}
	else if (discard_deck.size() > 0)
	{
		discard_deck.shuffling();
		p.cards << discard_deck;
		return success;
	}
	else
	{
		return noMoreCards;
	}
}

int SevenCardStud::after_turn(Player &p)
{
	return 0;
}

int SevenCardStud::before_round()
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

	// deal 3 cards to each player staring at the dealer
	for (int i = 0; i < 3; ++i)
	{
		for (auto p : players)
		{
			p->cards << main_deck;
		}
	}

	// 1st betting phase:
	// reset the records
	numOfFold = 0;
	for (auto p : players)
	{
		p->isFold = false;
		cout << p->username << ": * " << "* " << p->cards[2] << endl;
	}
	phase();

	return success;
}

int SevenCardStud::round()
{
	int result = success;
	for (int i = 0; i < 3; ++i)
	{
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
					cout << p->username << ": * " << "* ";
					for (int j = 2; j <= i + 3; ++j)
					{
						cout << p->cards[j] ;
					}
					cout << endl;
				}
			}
			phase();
		}
	}
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
				cout << p->username << ": * " << "* " << p->cards[2] << p->cards[3] << p->cards[4] << p->cards[5] << "*" << endl;
			}
		}
		phase();
	}
	return result;
}

void SevenCardStud::bestHand(Player &p)
{
	vector<Hand> handCombination; // store all the possible 5 card combinations of the 7 cards
	for (int i = 0; i < 7; ++i)
	{
		for (int j = i + 1; j < 7; ++j)
		{
			if (i != j)
			{
				Hand temp;
				for (int k = 0; k < 7; ++k)
				{
					if ((k != i) && (k != j))
					{
						temp.cards.push_back(p.cards[k]);
					}				
				}
				sort(temp.cards.begin(), temp.cards.end());
				handCombination.push_back(temp);
			}
		}
	}
	sort(handCombination.begin(),handCombination.end(),pokerRank1);
	p.cards = handCombination[0]; // update the player's hand to be the best ranking hand
}

int SevenCardStud::after_round()
{
	// sort the players by their best hands
	vector<shared_ptr<Player>> sortPlayers;
	for (auto p : players)
	{
		if (!p->isFold)
		{
			sort(p->cards.cards.begin(), p->cards.cards.end());
			cout << p->username << ": " << p->cards;
			bestHand(*p); // use each player's best possible hand
			cout << "Best is " << p->cards << endl;
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