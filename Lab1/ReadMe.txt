Jennie Liu
Lab 1

========================================================================
Errors & Warnings while Developing the Solution

Error:
1. In the definition of the ranking function, attempt to call the sort algorithm on each five cards of the card vector parameter.
   It's an error because the sort algorithm changes the object after ordering it, 
   but the parameter of this ranking function is a reference to a const vector of cards which cannot be changed.

2. use code:
   if (rankedCards[i].s == rankedCards[i + 1].s == rankedCards[i + 2].s == rankedCards[i + 3].s == rankedCards[i + 4].s)
   correct code should be:
   if (rankedCards[i].s == rankedCards[i + 1].s && rankedCards[i].s == rankedCards[i + 2].s 
	&& rankedCards[i].s == rankedCards[i + 3].s && rankedCards[i].s == rankedCards[i + 4].s)

========================================================================
Different Return Values and Their Meanings

Return Values		Meanings
      -1		No file was given.
       0		Succeed.
       1		Invalid file name was given; or the file didn't exist in the directory. 
       2		The file was read. But no valid hand was in the file.

========================================================================
Tests

   Commands			Program Outputs

1. Lab0				Purpose: This program reads and parses some card definition strings from a text file.
				Usage: Enter the file's name after the program's name, like 
				Lab0 card_file.txt
   This is correct, because I didn't enter any file's name in the command line. 
   The program can't read any file, so it goes to the help function to inform me about the right usage of the program.

2. Lab0 hands			Fail to open the file.
   This is correct, because I didn't enter a valid file's name (it should has suffix.txt).

3. Lab card_file.txt		The file contains no valid card definition string.
   This is correct, because in the file I put some invalid words instead of any valid card definition strings.
   The program reads the file, but put nothing in the card vector.

4. Lab hands.txt		Not five cards in the hand!
				Not five cards in the hand!
				Invalid card: wc
				no rank
				full house
				straight flush
				:
				:   (results as shown in the sample hands.txt)
				2C
				2D
				2H
				:
				:  (printing all the cards of valid hands in the sample hands.txt in order)

   The outcome is as expected. The program reads the hands.txt sample in which I also added one invalid card definition string "wc" 
   to check if the program prints it out as a invalid card.