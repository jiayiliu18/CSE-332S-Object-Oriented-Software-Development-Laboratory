Jennie Liu
Lab 2

========================================================================
Errors & Warnings
========================================================================
1.	C2061 / C2809 / C2805 / C2248
	I think the main problem is:
	in the definition of << operator which takes both a Hand and a Deck object (in function_operator.cpp), 
	Deck's member variable cannot be accessed.
   
   	Solution: In Deck.h, add a class declaration of Hand with no definition before declaring << operator to be friend of Deck.
		  In Hand.h, add a class declaration of Deck with no definition before declaring << operator to be friend of Hand.

2. 	C1010
	Forget to include "stdafx.h" to function_operator.cpp

3.	C4716
	Forget to add a return value for  Hand::operator=  

========================================================================
Different Return Values of the Main Function and Their Meanings
========================================================================
Return Values		Meanings
       0		Success
       1		More than 2 command line arguments are given. 
       2		Only one command line argument is given but it contains "-shuffle".
       3		Two command line arguments are given but neither one contains "-shuffle".
       4		No command line arguments are given.
       5		The file cannot be open.

========================================================================
Tests
========================================================================
Case 1:		Only give the program's name / Give more than two arguments / Give only one argument but contains -shuffle / Give two arguments without containing -shuffle

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		This program reads and parses some card definition strings from a text file.
		You can enter the file's name after the program's name, and tpye -shuffle if you want to shuffle cards.
		Example:
		Lab2 card_file.txt
		Or:
		Lab2 card_file.txt -shuffle
		------------------------------------------------------------------------------------------------------

Case 2:		Give an invalid file name

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		Cannot open the file. Be sure the file name is valid.
		------------------------------------------------------------------------------------------------------

Case 3:		Only give the file's name / Give the file name and -shuffle

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		After dealing, the deck remains:
		(here shows 7 card strings)
		hand1: ---
		hand2: ---
		:
		:
		After sorting by <:
		hand1: ---
		hand2: ---
		:
		:
		After sorting by poker rank:
		hand1: ---
		hand2: ---
		:
		:
		------------------------------------------------------------------------------------------------------