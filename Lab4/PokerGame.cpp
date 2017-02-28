// PokerGame.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the PokerGame class member functions
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "PokerGame.h"
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

// constructor:
PokerGame::PokerGame()
{
	main_deck.newDeck();
}

int PokerGame::before_turn(Player &p)
{
	return 0;
}

int PokerGame::turn(Player &p)
{
	return 0;
}

int PokerGame::after_turn(Player &p)
{
	return 0;
}

int PokerGame::before_round()
{
	return 0;
}
int PokerGame::round()
{
	return 0;
}
int PokerGame::after_round()
{
	return 0;
}

// betting phase
void PokerGame::phase()
{
	// isBet: is true if someone bets in a rotation
	// isRaise: is true if someone raises in a rotation
	// bet: the highest bet in the phase
	bool isBet = false, isRaise = false;
	unsigned int bet = 0;

	// reset all players' record
	for (auto p : players)
	{
		p->bet = 0;
	}

	for (auto p : players)
	{
		if (!p->isFold)   // if the player is in the round
		{
			cout << endl << p->username << ": ";
			if (p->noChip())
			{
				cout << "You have run out of chips! But you can remain in the round to see if you can win the pot!" << endl;
			}
			else
			{
				cout << "Enter the action you want to take:";
				if (!isBet)  // no one has bet
				{
					cout << " bet_1_chip, " << "bet_2_chips, " << "check, " << "or fold" << endl;
					string resp;
					while (cin >> resp)
					{
						if (resp == "bet_1_chip")
						{
							bet = 1;
							cout << "Cumulative bet is now " << bet << endl << endl;
							isBet = true;
							p->chips = p->chips - bet;
							p->bet = bet;
							break;
						}
						else if (resp == "bet_2_chips")
						{
							if (p->chips > 1)
							{
								bet = 2;
								cout << "Cumulative bet is now " << bet << endl << endl;
								isBet = true;
								p->chips = p->chips - bet;
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only 1 chip left. Choose another action." << endl;
							}
						}
						else if (resp == "check")
						{
							cout << "Cumulative bet is now " << bet << endl << endl;
							break;
						}
						else if (resp == "fold")
						{
							cout << "Cumulative bet is now " << bet << endl << endl;
							for (int i = 0; i < p->cards.size(); ++i)
							{
								Card c = p->cards.remove_card(i);
								discard_deck.add_card(c);
							}
							p->isFold = true;
							++numOfFold;
							pot = pot + p->bet;
							p->bet = 0;
							break;
						}
						else
						{
							cout << "Invalid action. Try again." << endl;
						}
					}
				}
				else
				{
					cout << " raise_1_chip, " << "raise_2_chips, " << "call, " << "or fold" << endl;
					string resp;
					while (cin >> resp)
					{
						if (resp == "raise_1_chip")
						{
							if (p->chips > bet)
							{
								bet = bet + 1;
								cout << "Cumulative bet is now " << bet << endl << endl;
								isRaise = true;
								p->chips = p->chips - bet;
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "raise_2_chips")
						{
							if (p->chips > bet + 1)
							{
								bet = bet + 2;
								cout << "Cumulative bet is now " << bet << endl << endl;
								isRaise = true;
								p->chips = p->chips - bet;
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "call")
						{
							if (p->chips >= bet)
							{
								cout << "Cumulative bet is now " << bet << endl << endl;
								p->chips = p->chips - bet;
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. All will be pushed into the pot."
									<< " You can stay in the game until the round is over." << endl;
								p->chips = 0;
								p->bet = bet;
								break;
							}
						}
						else if (resp == "fold")
						{
							cout << "Cumulative bet is now " << bet << endl << endl;
							for (int i = 0; i < p->cards.size(); ++i)
							{
								Card c = p->cards.remove_card(i);
								discard_deck.add_card(c);
							}
							p->isFold = true;
							++numOfFold;
							pot = pot + p->bet;
							p->bet = 0;
							break;
						}
						else
						{
							cout << "Invalid action. Try again." << endl;
						}
					}
				}
			}
		}
	}

	if (isBet)  // if someone bet from the last rotation
	{
		for (auto p : players)
		{
			if ((!p->isFold) && (p->bet < bet))  // for the players still in the round and do not reach the highest bet
			{
				cout << endl << p->username;
				if (p->noChip())
				{
					cout << ": you have run out of chips! But you can remain in the round to see if you can win the pot!" << endl;
				}
				else
				{
					cout << ": you can raise_1_chip, raise_2_chips, call or fold" << endl;
					string resp;
					while (cin >> resp)
					{
						if (resp == "raise_1_chip")
						{
							if (p->chips > bet)
							{
								bet = bet + 1;
								cout << "Cumulative bet is now " << bet << endl << endl;
								isRaise = true;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "raise_2_chips")
						{
							if (p->chips > bet + 1)
							{
								bet = bet + 2;
								cout << "Cumulative bet is now " << bet << endl << endl;
								isRaise = true;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "call")
						{
							if (p->chips >= bet)
							{
								cout << "Cumulative bet is now " << bet << endl << endl;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. All will be pushed into the pot."
									<< " You can stay in the game until the round is over." << endl;
								p->chips = 0;
								p->bet = bet;
								break;
							}
						}
						else if (resp == "fold")
						{
							cout << "Cumulative bet is now " << bet << endl << endl;
							for (int i = 0; i < p->cards.size(); ++i)
							{
								Card c = p->cards.remove_card(i);
								discard_deck.add_card(c);
							}
							p->isFold = true;
							++numOfFold;
							pot = pot + p->bet;
							p->bet = 0;
							break;
						}
						else
						{
							cout << "Invalid action. Try again." << endl;
						}
					}
				}
			}
		}
	}

	while (isRaise)  // if someone raised from the last rotation
	{
		isRaise = false;
		for (auto p : players)
		{
			if ((!p->isFold) && (p->bet < bet))  // for the players still in the round and do not reach the highest bet
			{
				cout << p->username << endl;
				if (p->noChip())
				{
					cout << ": you have run out of chips! But you can remain in the round to see if you can win the pot!" << endl;
				}
				else
				{
					cout << ": you can raise_1_chip, raise_2_chips, call or fold" << endl;
					string resp;
					while (cin >> resp)
					{
						if (resp == "raise_1_chip")
						{
							if (p->chips > bet)
							{
								bet = bet + 1;
								cout << "Cumulative bet is now " << bet << endl;
								isRaise = true;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "raise_2_chips")
						{
							if (p->chips > bet + 1)
							{
								bet = bet + 2;
								cout << "Cumulative bet is now " << bet << endl;
								isRaise = true;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. Choose another action." << endl;
							}
						}
						else if (resp == "call")
						{
							if (p->chips >= bet)
							{
								cout << "Cumulative bet is now " << bet << endl;
								p->chips = p->chips - (bet - p->bet);
								p->bet = bet;
								break;
							}
							else
							{
								cout << "You have only " << p->chips << " chips left. All will be pushed into the pot."
									<< " You can stay in the game until the round is over." << endl;
								p->chips = 0;
								p->bet = bet;
								break;
							}
						}
						else if (resp == "fold")
						{
							cout << "Cumulative bet is now " << bet << endl;
							for (int i = 0; i < p->cards.size(); ++i)
							{
								Card c = p->cards.remove_card(i);
								discard_deck.add_card(c);
							}
							p->isFold = true;
							++numOfFold;
							pot = pot + p->bet;
							p->bet = 0;
							break;
						}
						else
						{
							cout << "Invalid action. Try again." << endl;
						}
					}
				}
			}
		}
	}
	// after the betting phase, push all the remaining players' bets into the pot
	for (auto p : players)
	{
		if (!p->isFold)
		{
			pot = pot + p->bet;
		}
	}
}

void PokerGame::resetOrLeave()
{
	for (size_t j = 0; j < players.size(); ++j)
	{
		if (players[j]->noChip())
		{
			cout << players[j]->username << " has run out of chip! To reset chips, enter reset. To leave the game, enter leave." << endl;
			string resp;
			while (cin >> resp)
			{
				if (resp == "reset")
				{
					players[j]->chips = 20;
					break;
				}
				else if (resp == "leave")
				{
					string file = players[j]->username + ".txt";
					ofstream out(file.c_str());
					out << players[j]->wins << " " << players[j]->losses << " " << players[j]->chips;
					out.close();
					players.erase(players.begin() + j);
					--j;
					break;
				}
				else
				{
					cout << "Invalid action. Try again." << endl;
				}
			}
		}
	}
}