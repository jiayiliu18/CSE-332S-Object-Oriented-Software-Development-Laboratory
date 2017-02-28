Jennie Liu
Lab 0

========================================================================
Errors & Warnings while Developing the Solution

Error:
1. 'vector': undeclared identifier    in Card.h
    Miss std:: before vector<Card> in the function prototype.

Warning:
1. '<': signed/unsigned mismatch    in Lab0.cpp
   Miss unsigned label before the int iterator of a for loop.

========================================================================
Different Return Values and Their Meanings

Return Values		Meanings
      -1		No file was given.
       0		Succeed.
       1		Invalid file name was given; or the file didn't exist in the directory. 
       2		The file was read. But no valid card definition string was in the file.

========================================================================
Tests

   Commands			Program Outputs
1. Lab0				Purpose: This program reads and parses some card definition strings from a text file.
				Usage: Enter the file's name after the program's name, like 
				Lab0 card_file.txt
   This is correct, because I didn't enter any file's name in the command line. 
   The program can't read any file, so it goes to the help function to inform me about the right usage of the program.

2. Lab0 card_file		Fail to open the file.
   This is correct, because I didn't enter a valid file's name (it should has suffix .txt).

3. Lab card_file.txt		The file contains no valid card definition string.
   This is correct, because in the file I put some invalid words instead of any valid card definition strings.
   The program reads the file, but put nothing in the card vector.

4. Lab card_file.txt		2C
				10D
				AH
				3S
				JD
   This is correct. The program reads and print out all the valid card string in the given file, and skip those invalid ones.