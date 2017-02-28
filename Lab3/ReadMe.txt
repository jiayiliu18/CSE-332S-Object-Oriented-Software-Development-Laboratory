Jennie Liu   jiayiliu@wustl.edu  Zhihao Rong zrong@wustl.edu
Lab 3

========================================================================
Errors & Warnings
========================================================================
1.	C4996
	using 'strcpy' may be unsafe.

2. 	LNK2001 and LNK1120
	unresolved external
	I didn't initialize the static member variable of the Game class (the smart pointer points to the Game object).

========================================================================
Different Return Values of the Main Function and Their Meanings
========================================================================
Return Values		Meanings
       0		Success
       -1		No more cards to deal 
       1		Less than 3 command line arguments is given
       2		The first commend line argument does not contain FiveCardDraw
       3		The game is not started

========================================================================
Tests
========================================================================
Case 1:		Give less than 3 arguments, such as:
		Lab3 FiveCardDraw jennie

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		This program supports the five card draw game.
		Enter the game name FiveCardDraw followed by the names of the player.
		There should be at least two players to start the game.
		And the name of the players should be only one word starting with a letter.
		------------------------------------------------------------------------------------------------------

Case 2:		The first commend line argument does not contain FiveCardDraw, such as:
		Lab3 FiveCard jennie tony 

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		unknown game
		instance not available
		------------------------------------------------------------------------------------------------------

Case 3:		Lab3 FiveCardDraw jennie tony helen

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		jennie
		added

		tony
		added

		helen 
		added

		tony:
		7H 9S JH QS AH
		
		Enter the position of the cards to discard sequentially, starting at 0
		If you finish, enter n
		If no card to discard, enter n
		4 n  (entered by user)
		
		helen:
		3H 3S 6D 7S 10S
		
		Enter the position of the cards to discard sequentially, starting at 0
		If you finish, enter n
		If no card to discard, enter n
		1 4 n  (entered by user)
		
		jennie:
		4D 8C 6D 7S 10S

		Enter the position of the cards to discard sequentially, starting at 0
		If you finish, enter n
		If no card to discard, enter n
		2 3 n  (entered by user)
		
		tony:
		7H 9S JH QS QH

		helen:
		3H 6D 7S 8S KD

		jennie:
		2H 4D 8C 9D AS

		tony
		number of wins: 1 number of losses: 0
		7H 9S JH QS QH

		jennie:
		number of wins: 0 number of losses: 1
		2H 4D 8C 9D AS

		helen:
		number of wins: 0 number of losses: 1
		3H 6D 7S 8S KD

		Do you want to leave? If so, type your name, otherwise type no
		tony

		Do you want to leave? If so, type your name, otherwise type no
		jennie
				
		Do you want to leave? If so, type your name, otherwise type no
		no

		Do you want to join? If so, type your name, otherwise type no
		lee

		(Then start a new game with helen and lee)
		:
		:
		:
		------------------------------------------------------------------------------------------------------