// Game.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Game class
#pragma once
#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>
#include <string>
#include "Deck.h"
#include "Player.h"

// abstract base class
class Game
{
public:
	static std::shared_ptr<Game> instance();
	static void start_game(const string &);
	static void stop_game();
	void add_player(const string &);
	std::shared_ptr<Player> find_player(const string &);
	size_t numOfPlayers();
	// destructor:
	virtual ~Game() = default;
	// pure virtual:
	virtual int before_turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;

// member variables:
protected:
	static std::shared_ptr<Game> game;
	Deck main_deck;
	vector<std::shared_ptr<Player>> players;
};
#endif