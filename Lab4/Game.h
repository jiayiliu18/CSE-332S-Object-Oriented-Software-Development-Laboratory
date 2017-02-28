// Game.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Game class, which is the abstract base class of all other games
// Declaration of the pokerRank functions and the usage function
#pragma once
#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>
#include <string>
#include "Deck.h"
#include "Player.h"
#include "Hand.h"

class Game
{
public:
	// common functionality shared by all games:
	static std::shared_ptr<Game> instance();
	static void start_game(const string &);
	static void stop_game();
	void add_player(const string &);
	std::shared_ptr<Player> find_player(const string &);
	size_t numOfPlayers();

	// destructor:
	virtual ~Game() = default;

	// pure virtual:
	// each game defines its own version
	virtual int before_turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	virtual void phase() = 0;
	virtual void resetOrLeave() = 0;

	// member variables:
	vector<std::shared_ptr<Player>> players;
protected:
	static std::shared_ptr<Game> game;
	Deck main_deck;
	unsigned int pot = 0;
};

// Declaration of the pokerRank function which calls another function (ranking).
bool pokerRank2(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
bool pokerRank1(const Hand & h1, const Hand & h2);
int ranking(const Hand & h);

// Declaration of the usage function which tells how to use the program correctly
int usage(char *index);
#endif