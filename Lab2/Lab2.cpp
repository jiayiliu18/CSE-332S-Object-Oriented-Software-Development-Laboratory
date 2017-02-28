// Lab2.cpp
// Author: Jennie Liu   jiayiliu@wustl.edu
// The purpose of this program is to parse a file containing card definition strings; store the cards in a deck; deal cards to hands; and indicate hand ranking. 

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	const int maxArgc = 3;
	const int minArgc = 2;
	const int progNameIdex = 0;
	string isShuffle = "-shuffle";
	vector<Hand> hands;  // contains nine hands
	Hand h;
	int numOfHands = 9;
	int numOfCards = 5;
	const int success = 0;
	const int invalidFile = 5;

	// more than 2 command line arguments are given in addition to the program name
	if (argc > maxArgc)
	{
		return usage(argv[progNameIdex], "tooMuchArg");
	}

	// no command line arguments are given instead of the program name
	else if (argc < minArgc)
	{
		return usage(argv[progNameIdex], "tooFewArg");
	}

	// only one command line argument is given
	else if (argc == minArgc)
	{
		string firstArg(argv[1]);

		//but it contains "-shuffle"
		if (firstArg.find(isShuffle) != std::string::npos)
		{
			return usage(argv[progNameIdex], "oneButShuffle");
		}

		// the file name is given, and do not need to shuffle
		else
		{
			try
			{
				Deck deck = Deck(argv[1]);
				for (int i = 0; i < numOfHands; ++i)
				{
					hands.push_back(h);
				}

				// dealing cards
				for (int j = 0; j < numOfCards; ++j)
				{
					for (int i = 0; i < numOfHands; ++i)
					{
						hands[i] << deck;
					}
				}

				// printing out
				cout << "After dealing, the deck remains:" << endl << deck << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}

				// sort the hands according to < 
				sort(hands.begin(), hands.end());
				cout << "After sorting by <:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}

				// sort the hands according to poker rank
				sort(hands.begin(), hands.end(), pokerRank);
				cout << "After sorting by poker rank:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}
				return success;
			}
			catch (runtime_error err)
			{
				cout << err.what() << " Be sure the file name is valid." << endl;
				return invalidFile;
			}
		}
	}

	// two command line arguments are given
	else
	{
		string firstArg(argv[1]);
		string secondArg(argv[2]);

		// the first argument indicate to shuffle
		if (firstArg.find(isShuffle) != std::string::npos)
		{
			try
			{
				Deck deck = Deck(argv[2]);
				deck.shuffling();
				for (int i = 0; i < numOfHands; ++i)
				{
					hands.push_back(h);
				}

				// dealing cards
				for (int j = 0; j < numOfCards; ++j)
				{
					for (int i = 0; i < numOfHands; ++i)
					{
						hands[i] << deck;
					}
				}

				// printing out
				cout << "After dealing, the deck remains:" << endl << deck << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand"<< i << ": " << hands[i] << endl;
				}

				// sort the hands according to < 
				sort(hands.begin(), hands.end());
				cout << "After sorting by <:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}

				// sort the hands according to poker rank
				sort(hands.begin(), hands.end(), pokerRank);
				cout << "After sorting by poker rank:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}
				return success;
			}
			catch (runtime_error err)
			{
				cout << err.what() << " Be sure the file name is valid." << endl;
				return invalidFile;
			}
		}

		// the second argument indicate to shuffle
		else if (secondArg.find(isShuffle) != std::string::npos)
		{
			try
			{
				Deck deck = Deck(argv[1]);
				deck.shuffling();
				for (int i = 0; i < numOfHands; ++i)
				{
					hands.push_back(h);
				}

				// dealing cards
				for (int j = 0; j < numOfCards; ++j)
				{
					for (int i = 0; i < numOfHands; ++i)
					{
						hands[i] << deck;
					}
				}

				// printing out
				cout << "After dealing, the deck remains:" << endl << deck << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}

				// sort the hands according to < 
				sort(hands.begin(), hands.end());
				cout << "After sorting by <:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}

				// sort the hands according to poker rank
				sort(hands.begin(), hands.end(), pokerRank);
				cout << "After sorting by poker rank:" << endl;
				for (int i = 0; i < numOfHands; ++i)
				{
					cout << "hand" << i << ": " << hands[i] << endl;
				}
				return success;
			}
			catch (runtime_error err)
			{
				cout << err.what() << " Be sure the file name is valid." << endl;
			}
		}

		// neither one contains "-shuffle"
		else
		{
			return usage(argv[progNameIdex], "twoWithoutShuffle");
			return invalidFile;
		}
	}
}

