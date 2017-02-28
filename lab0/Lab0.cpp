// Lab0.cpp 
// Author: Jennie Liu   jiayiliu@wustl.edu
// Definitions for a file reading and parsing program, which reads files of card definition strings and outputs valid card strings.   

#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

enum returnVal { missFileName = -1, success = 0, invalidFileName = 1, invalidFileContent = 2};

// the file parsing function,
// which reads and parses valid card definition strings from a file into a vector of Card.
int parsing(vector<Card> &cards, char *fname) 
{
	const int minStringSize = 2; 
	const int maxStringSize = 3;
	const int first = 0;
	const int second = 1;
	const int third = 2;

	ifstream ifs(fname);
	string c;
	Card card;

	if (ifs.is_open()) 
		{	
		while (ifs >> c) 
			{
			if (c.size() == minStringSize)
				{
				
				if (c[second] == 'C' || c[second] == 'c' || c[second] == 'H' || c[second] == 'h' || c[second] == 'S' || c[second] == 's' || c[second] == 'D' || c[second] == 'd')
					{
					switch (c[second])
						{
						case 'C': case 'c': card.s = Card::suit::clubs; break;
						case 'D': case 'd': card.s = Card::suit::diamonds; break;
						case 'H': case 'h': card.s = Card::suit::hearts; break;
						case 'S': case 's': card.s = Card::suit::spades; break;
						}

					switch (c[first])
						{
						case '2': card.r = Card::rank::two; cards.push_back(card); break;
						case '3': card.r = Card::rank::three; cards.push_back(card); break;
						case '4': card.r = Card::rank::four; cards.push_back(card); break;
						case '5': card.r = Card::rank::five; cards.push_back(card); break;
						case '6': card.r = Card::rank::six; cards.push_back(card); break;
						case '7': card.r = Card::rank::seven; cards.push_back(card); break;
						case '8': card.r = Card::rank::eight; cards.push_back(card); break;
						case '9': card.r = Card::rank::nine; cards.push_back(card); break;
						case 'J': case 'j': card.r = Card::rank::jack; cards.push_back(card); break;
						case 'Q': case 'q': card.r = Card::rank::queen; cards.push_back(card); break;
						case 'K': case 'k': card.r = Card::rank::king; cards.push_back(card); break;
						case 'A': case 'a': card.r = Card::rank::ace; cards.push_back(card); break;
						}
					}
				}

			else if (c.size() == maxStringSize)
				{
				if (c[first] == '1' && c[second] == '0') 
					{
					card.r = Card::rank::ten;
					
					switch (c[third]) 
						{
						case 'C': case 'c': card.s = Card::suit::clubs; cards.push_back(card); break;
						case 'D': case 'd': card.s = Card::suit::diamonds; cards.push_back(card); break;
						case 'H': case 'h': card.s = Card::suit::hearts; cards.push_back(card); break;
						case 'S': case 's': card.s = Card::suit::spades; cards.push_back(card); break;
						}
					}				
				}

			// if the card definition string is not 2 or 3 char long, skip it
			else {}
			}

		ifs.close();
		return success;
		}

	// if the name of the file is invalid; or the file doesn't exist
	else 
		{
		cerr << "Fail to open the file." << endl;
		return invalidFileName;
		}
}


// print out valid card strings from the file
int printing(const vector<Card> &cards) 
{
	const int minCardNum = 1;

	// when the file contains valid card strings
	if (cards.size() >= minCardNum)
		{
		string c;
		for (unsigned int i = 0; i < cards.size(); ++i)
			{
			switch (cards[i].r)
				{
				case Card::rank::two: c = "2"; break;
				case Card::rank::three: c = "3"; break;
				case Card::rank::four: c = "4"; break;
				case Card::rank::five: c = "5"; break;
				case Card::rank::six: c = "6"; break;
				case Card::rank::seven: c = "7"; break;
				case Card::rank::eight: c = "8"; break;
				case Card::rank::nine: c = "9"; break;
				case Card::rank::ten: c = "10"; break;
				case Card::rank::jack: c = "J"; break;
				case Card::rank::queen: c = "Q"; break;
				case Card::rank::king: c = "K"; break;
				case Card::rank::ace: c = "A"; break;
				}

			switch (cards[i].s) 
				{
				case Card::suit::clubs: c += "C"; break;
				case Card::suit::diamonds: c += "D"; break;
				case Card::suit::hearts: c += "H"; break;
				case Card::suit::spades: c += "S"; break;
				}

			cout << c << endl;
			}
		return success;
		}
	
	else
		{
		cerr << "The file contains no valid card definition string." << endl;
		return invalidFileContent;
		}
}


// the help function that tells how to use the program correctly
int usage(char *pname) 
{
	cout << "Purpose: This program reads and parses some card definition strings from a text file." << endl 
		<< "Usage: Enter the file's name after the program's name, like " << endl
		<< pname << " card_file.txt" << endl;
	return missFileName;
}


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

		// if parsing suceeded, then print out valid card strings
		else 
			{
			return printing(cards);
			}
		}
}

