// Player.cpp
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the Player struct member functions and its non-member functions

#include "stdafx.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

// constructor
Player::Player(const char *name)
{
	string input = name;
	username = input;
	string fname = input + ".txt";
	ifstream ifs(fname.c_str());
	if (ifs.is_open())
	{
		ifs >> wins;
		ifs >> losses;
		ifs >> chips;
	}
	ifs.close();
}

bool Player::noChip()
{
	return (chips == 0) || (chips>4000000000);
}

// insertion operator
ostream & operator<<(ostream & out, const Player & player)
{
	out << player.username << " wins " << player.wins << " times and loses " << player.losses << " times, with " << player.chips << " chips." << endl;
	return out;
}