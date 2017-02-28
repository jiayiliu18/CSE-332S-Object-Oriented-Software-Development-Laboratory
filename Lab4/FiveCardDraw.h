// FiveCardDraw.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the FiveCardDraw class, which derived from PokerGame
#pragma once
#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include "PokerGame.h"
#include <memory>

class FiveCardDraw : public PokerGame
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
};
#endif