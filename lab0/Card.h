// Card.h
// Author: Jennie Liu    jiayiliu@wustl.edu
// Declarations for a file reading and parsing program, which reads files of card definition strings and outputs valid card strings.

#pragma once
#ifndef CARD_H
#define CARD_H
#include <vector>

// type Card, which has varible members suit and rank
struct Card
{
	enum struct suit {clubs, diamonds, hearts, spades};
	enum struct rank {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
	suit s;
	rank r;
};

// function declarations
int parsing(std::vector<Card> &cards, char *fname);
int printing(const std::vector<Card> &cards);
int usage(char *pname);

#endif // !CARD_H
