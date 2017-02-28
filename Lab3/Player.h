// Player.h
// Author: Jennie Liu   jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Player struct

#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Hand.h"

struct Player
{
	friend ostream & operator<<(ostream & out, const Player & player);
	// member variables:
	std::string username;
	Hand cards;
	unsigned int wins = 0, losses = 0;	
	// constructor:
	Player(const char *name);
};
// insertion operator
ostream & operator<<(ostream & out, const Player & player);
#endif
