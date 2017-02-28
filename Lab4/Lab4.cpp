// Lab4.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// This program supports the five card draw game and the seven card stud game for multiple players.

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Player.h"
#include "Game.h"
#include "PokerGame.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "myException.h"
using namespace std;

enum returnVal { success = 0, unknownGame = 2, noInstance = 3 };
int main(int argc, char *argv[])
{
	int result = success;
	const int minArgc = 4;
	if (argc < minArgc)
	{
		result = usage("tooFewArg");
	}
	else
	{
		PokerGame g;
		shared_ptr<Game> game;
		try
		{
			g.start_game(argv[1]);
		}
		catch (game_already_started)
		{
			cout << "game already started" << endl;
		}
		catch (unknown_game)
		{
			cout << "unknown game" << endl;
			result = unknownGame;
		}

		try
		{
			game = g.instance();
			for (int i = 2; i < argc; ++i)
			{
				try
				{
					cout << argv[i] << endl;
					game->add_player(argv[i]);
					cout << "added" << endl;
				}
				catch (already_playing)
				{
					cout << "is already playing" << endl;
				}
			}

			game->resetOrLeave();
			cout << endl;
			if (game->numOfPlayers() >= 2)
			{
				game->before_round();
				int r = game->round();
				if (r != 0)
				{
					result = r;
					cout << "run out of cards" << endl;
				}
				else
				{
					game->after_round();
				}
			}

			try
			{
				game->stop_game();
			}
			catch (no_game_in_progress)
			{
				cout << "no game in progress" << endl;
				result = noInstance;
			}
		}
		catch (instance_not_available)
		{
			cout << "instance not available" << endl;
			result = noInstance;
		}

		while (true)
		{
			cout << "Want to play a new game? Answer yes to start a new game. Enter anything else will exit the program." << endl;
			string resp;
			cin >> resp;
			if (resp == "yes")
			{
				cout << "Which game? FiveCardDraw or SevenCardStud" << endl;
				while (cin >> resp)
				{
					if (resp == "FiveCardDraw" || resp == "SevenCardStud")
					{
						g.start_game(resp);
						game = g.instance();
						break;
					}
					else
					{
						cout << "Invalid game name. Try again!" << endl;
					}
				}
				cout << "Enter the name of players, seperated by space." 
					<< " You should have at least 2 players to start the game." 
					<<" When you finish, enter n." << endl
					<< "Like: jennie tony helen n" << endl;
				while (cin >> resp)
				{
					if (resp == "n")
					{
						break;
					}
					else
					{
						try
						{
							game->add_player(resp);
						}
						catch (already_playing)
						{
							cout << "is already playing" << endl;
						}
					}
				}
				game->resetOrLeave();
				cout << endl;
				if (game->numOfPlayers() >= 2)
				{
					game->before_round();
					int r = game->round();
					if (r != 0)
					{
						result = r;
						cout << "run out of cards" << endl;
					}
					else
					{
						game->after_round();
					}
				}
				try
				{
					game->stop_game();
					cout << "Game stopped" << endl;
				}
				catch (no_game_in_progress)
				{
					cout << "no game in progress" << endl;
					result = noInstance;
				}
			}
			else
			{
				cout << "Leave the program." << endl;
				break;
			}
		}
	}
	return result;
}