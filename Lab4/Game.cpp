// Game.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Game class member functions 
// Definitions of the pokerRank functions and usage function
#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <string>
#include <cstring>
#include "myException.h"
using namespace std;

// static member variables need to be initialized before using them
shared_ptr<Game> Game::game(nullptr);

enum returnVal { success = 0, tooFewArg = 1 };

// returns the game if it has started
shared_ptr<Game> Game::instance()
{
	if (game == nullptr)
	{
		throw instance_not_available();
	}
	else
	{
		return game;
	}
}

// starts the game
void Game::start_game(const string & gname)
{
	if (game)
	{
		throw game_already_started();
	}
	else
	{		
		if (gname.find("FiveCardDraw") != string::npos)
		{
			game = make_shared<FiveCardDraw>();
		}
		else if (gname.find("SevenCardStud") != string::npos)
		{
			game = make_shared<SevenCardStud>();
		}
		else
		{
			throw unknown_game();
		}
	}
}

// stops the game
void Game::stop_game()
{
	if (game)
	{
		game = nullptr;
	}
	else
	{
		throw no_game_in_progress();
	}
}

// adds a player, throw an exception if the player is already in
void Game::add_player(const string &s)
{
	for (auto i : players)
	{
		if ((i->username) == s)
		{
			throw already_playing();
		}
	}
	shared_ptr<Player> p = make_shared<Player>(s.c_str());
	players.push_back(p);
}

// finds a player, returns a smart pointer to that player or nullprt if not found
shared_ptr<Player> Game::find_player(const string &s)
{
	shared_ptr<Player> result;
	for (auto i : players)
	{
		if ((i->username) == s)
		{
			result = i;
		}
	}
	return result;
}

// shows the number of players in the game
size_t Game::numOfPlayers()
{
	return players.size();
}

// returns true if the first hand is higher than the second
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
			return pokerRank1(p1->cards, p2->cards);
		}
	}
}

// This function also calls another ranking function which gives the rank group of each hand
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
					if (h2.cards[last].r == h1.cards[last].r)
					{
						if (h2.cards[sec].r == h1.cards[sec].r)
						{
							return (h2.cards[bgn].r < h1.cards[bgn].r);
						}
						else
						{
							return (h2.cards[sec].r < h1.cards[sec].r);
						}
					}
					else
					{
						return (h2.cards[last].r < h1.cards[last].r);
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

// returns a hand's rank group as an integer
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

// tells how to use the program correctly
int usage(char *index)
{
	cout << "This program supports the five card draw game and the seven card stud game for multiple players." << endl
		<< "Enter the game name FiveCardDraw or SevenCardStud followed by the names of the player." << endl
		<< "There should be at least two players to start the game." << endl
		<< "And the name of the players should be starting with a letter." << endl;

	return tooFewArg;
}