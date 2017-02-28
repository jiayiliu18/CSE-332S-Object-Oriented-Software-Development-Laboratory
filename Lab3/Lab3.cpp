// Lab3.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// This program supports a five card draw game.

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Player.h"
#include "Game.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "FiveCardDraw.h"
#include "myException.h"
using namespace std;

enum returnVal { success = 0, unknownGame = 2, noInstance = 3};
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
		FiveCardDraw g;
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
			auto game = g.instance();
			for (int i = 2; i < argc; ++i)
			{
				try
				{
					cout << argv[i] << endl;
					game->add_player(argv[i]);
					cout << "added" << endl << endl;
				}
				catch (already_playing)
				{
					cout << "already playing" << endl;
				}
			}
			cout << endl;
			size_t numPlayers = game->numOfPlayers();
			while (numPlayers >= 2)
			{
				game->before_round();
				int r = game->round();
				if (r != 0)
				{
					result = r;
					break;
				}
				game->after_round();
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
		catch (instance_not_available)
		{
			cout << "instance not available" << endl;
			result = noInstance;
		}	
	}
	return result;
}



