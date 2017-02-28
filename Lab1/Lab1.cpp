// Lab1.cpp 
// Author: Jennie Liu   jiayiliu@wustl.edu
// Definitions for a file reading and parsing program, which reads files of card definition strings and outputs their hand ranks and cards in order.

#include "stdafx.h"
#include "Card.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	const int minArgNum = 2;
	const int progNameIdex = 0;
	const int fileNameIdex = 1;

	// in case that the user doesn't enter the name of the card string file
	if (argc < minArgNum)
	{
		return usage(argv[progNameIdex]);
	}

	else
	{
		vector<Card> cards;
		int r = parsing(cards, argv[fileNameIdex]);

		// if parsing failed
		if (r)
		{
			return r;
		}

		// if parsing suceeded, 
		// then give the rank of each hand and print out valid card strings in order
		else
		{
			ranking(cards);
			sort(cards.begin(), cards.end());
			return printing(cards);
		}
	}
}


