// PokerGame.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the PokerGame class, which derived from Game
#pragma once
#ifndef POKERGAME_H
#define POKERGAME_H
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include <memory>

class PokerGame : public Game
{
public:
	// constructor:
	PokerGame();
	// the virtuals:
	int before_turn(Player &);
	int turn(Player &);
	int after_turn(Player &);
	int before_round();
	int round();
	int after_round();
	// here we add a new member function which manipulates a betting phase
	void phase();
	// here we add a new member function which asks the players who run out of chips to reset or leave
	void resetOrLeave();

	// member variables:
protected:
	size_t dealer = 0;
	Deck discard_deck;
	unsigned int numOfFold = 0;  // numOfFold: number of players who fold
};
#endif