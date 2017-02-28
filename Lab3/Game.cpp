// Game.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Game class member functions 

#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <string>
#include <cstring>
#include "myException.h"
using namespace std;

shared_ptr<Game> Game::game(nullptr);

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
		if (gname.find("FiveCardDraw") == string::npos)
		{
			throw unknown_game();
		}
		else
		{
			game = make_shared<FiveCardDraw>();
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
	shared_ptr<Player> p = make_shared<Player>(s.c_str());
	for (auto i : players)
	{
		if ((i->username) == (p->username))
		{
			throw already_playing();
		}
	}
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
