// SevenCardStud.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the SevenCardStud class, which derived from PokerGame
#pragma once
#ifndef SEVENCARDSTUD_H
#define SEVENCARDSTUD_H
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include "PokerGame.h"
#include <memory>

class SevenCardStud : public PokerGame
{
public:
	// constructor:
	SevenCardStud();
	// the virtuals:
	int before_turn(Player &) override;
	int turn(Player &) override;
	int after_turn(Player &) override;
	int before_round() override;
	int round() override;
	int after_round() override;

	// here we add a function to find out the best hand among the 7 cards of a player
private:
	void bestHand(Player &);
};
#endif
