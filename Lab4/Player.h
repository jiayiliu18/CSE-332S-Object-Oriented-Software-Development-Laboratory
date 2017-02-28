// Player.h
// Author: Jennie Liu   jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Player struct and declaration of its non-member function

#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Hand.h"

struct Player
{
	// member variables:
	std::string username;
	Hand cards;
	unsigned int wins = 0, losses = 0, chips = 20;
	// we need to keep track of each player that whether she folds (drops the round)
	bool isFold = false;
	// we need to keep track of the number of chips each player has bet in a betting phase
	unsigned int bet = 0;
	// constructor:
	Player(const char *name);
	// here we add a new member function, which returns true if the player runs out of chips
	bool noChip();
};
// insertion operator
ostream & operator<<(ostream & out, const Player & player);
#endif