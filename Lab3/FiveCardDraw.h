// FiveCardDraw.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the FiveCardDraw class
// Declaration of the pokerRank functions and the usage function
#pragma once
#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include <memory>

class FiveCardDraw : public Game
{
public:
	// constructor:
	FiveCardDraw();
	// the virtuals:
	int before_turn(Player &) override;
	int turn(Player &) override;
	int after_turn(Player &) override;
	int before_round() override;
	int round() override;
	int after_round() override;

// member variables:
protected:
	size_t dealer = 0;
	Deck discard_deck;
};

// Declaration of the pokerRank function which calls another function (ranking).
bool pokerRank2(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
bool pokerRank1(const Hand & h1, const Hand & h2);
int ranking(const Hand & h);

// Declaration of the usage function which tells how to use the program correctly
int usage(char *index);
#endif