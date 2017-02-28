Jennie Liu   jiayiliu@wustl.edu  
Zhihao Rong   zrong@wustl.edu
Lab 4

========================================================================
Errors & Warnings
========================================================================
1.	signed and unsigend mismatch
	In some of the for loops, we mismatched int and size_t type variables.

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
Some Design Ideas
========================================================================
We add and modify some functions:

1. In Card.h, we add a << operator to print out a single card, which is needed in the SevenCardStud game, that only parts of the 
   hand are printed.

2. In Hand.cpp, we modify the definition of << operator which deals a card from a deck to a hand.
   The original version sorts the hand after dealing. But we remove this, 
   considering that in the SevenCardStud game when we print out the face-down and face-up cards, 
   they should be in the order of dealing not value.

3. In Deck.h and Deck.cpp, we declare and define a newDeck member funtion, 
   which generates a new deck containing 52 different permutations of the cards.

4. In Player.h, we add a isFold data member to keep track of whether the player folds (drops the round).

   A bet data member to keep track of the number of chips that the player has spend in the current phase.

   A noChip member function, which returns true if the player has run out of chips.
 
5. In Game.h and Game.cpp, we declare and define a numOfPlayers member function,
   which returns the number of players in the game.

   A pure virtual member function phase, which handles a betting phase.
   
   A pure virtual member funtion resetOrLeave, which asks the players who have run out chips to reset their chips or leave the game.

6. We add a PokerGame class, which derived from Game and are inherited by FiveCardDraw and SevenCardStud.
   
   This class defines the phase and resetOrLeave functions, which will be used in both FiveCardDraw and SevenCardStud.
   
   We also add a numOfFold data member to keep track of the number of players who fold.

7. In SevencardStud class, we add a bestHand member function to find out the best hand among the 7 cards of the player.
 
========================================================================
Tests
========================================================================
Case 1:		Give less than 3 arguments, such as:
		Lab4 FiveCardDraw jennie

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		This program supports the five card draw game and the seven card stud game for multiple players.
		Enter the game name followed by the names of the player.
		There should be at least two players to start the game.
		And the name of the players should be starting with a letter.
		------------------------------------------------------------------------------------------------------

Case 2:		The first commend line argument does not contain FiveCardDraw or SevenCardStud, such as:
		Lab4 FiveCard jennie tony 

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		unknown game
		instance not available
		Want to play a new game? Answer yes to start a new game. Enter anything else will exit the program. 
		------------------------------------------------------------------------------------------------------
		If you enter anything instead of yes, the program outputs:
		------------------------------------------------------------------------------------------------------
		Leave the program.  
		------------------------------------------------------------------------------------------------------
		If you enter yes, the program outputs:
		------------------------------------------------------------------------------------------------------
		Which game? FiveCardDraw or SevenCardStud
		------------------------------------------------------------------------------------------------------
		If you enter something not FiveCardDraw or SevenCardStud, the program repeats asking:
		------------------------------------------------------------------------------------------------------
		Invalid game name. Try again!
		------------------------------------------------------------------------------------------------------
		If you enter FiveCardDraw or SevenCardStud, the program outputs:
		------------------------------------------------------------------------------------------------------
		Enter the name of players, seperated by space. You should have at least 2 players to start the game.
		When you finish, enter n.
		Like: jennie tony helen n
		------------------------------------------------------------------------------------------------------
		If you enter something like jennie tony helen n, the program starts the game as Case 3 does.

Case 3:		
		If you run the program with the command: Lab4 SevenCardStud jennie tony helen
		Or continue from the last case,

		Program Outputs:
		------------------------------------------------------------------------------------------------------
		jennie
		added
		tony
		added
		helen 
		added
		------------------------------------------------------------------------------------------------------
		Here I set jennie is out of chips, so the program prompts:
		------------------------------------------------------------------------------------------------------
		jennie has run out of chips! To reset chips, enter reset. To leave the game, enter leave.
		------------------------------------------------------------------------------------------------------
		If you enter leave, jennie is kicked out of the game. The program will continue the game with tony and helen.
		If yoy enter something instead of leave or reset, the promgram will prompt: Invalid action! Try again!
		If you enter reset, then jennie's chips reset to 20, and the program continues:
		------------------------------------------------------------------------------------------------------
		tony: * * QD
		helen: * * AD
		jennie: * * QS
		
		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		call (input)
		Invalid action. Try again.
		check
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		bet_1_chip(input)
		Cumulative bet is now 1

		jennie: Enter the action you want to take: raise_1_chip, raise_2_chips, call, or fold
		raise_2_chips(input)
		Cumulative bet is now 3

		tony: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		Cumulative bet is now 3

		helen: you can raise_1_chip, raise_2_chips, call, or fold
		raise_1_chips(input)
		Cumulative bet is now 4

		jennie: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		Cumulative bet is now 4

		tony: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		Cumulative bet is now 4

		tony: * * QD 9S
		helen: * * AD 4D
		jennie: * * QS 9H
		
		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		jennie: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		bet_1_chip
		Cumulative bet is now 1

		tony: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		Cumulative bet is now 1

		helen: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		Cumulative bet is now 1

		tony: * * QD 9S QH
		helen: * * AD 4D 10C
		jennie: * * QS 9H 6S
		
		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		jennie: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: * * QD 9S QH JC
		helen: * * AD 4D 10C 10S
		jennie: * * QS 9H 6S 7D

		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		jennie: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: * * QD 9S QH JC *
		helen: * * AD 4D 10C 10S *
		jennie: * * QS 9H 6S 7D *

		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		jennie: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: 2S 9S JC JS QD QH AS 
		Best is JC JS QD QH AS

		helen: 3C 4C 4D 10C 10H 10S AD
		Best is 4C 4D 10C 10H 10S

		jennie: 2D 6D 6S 7D 9H JD QS	
		Best is 6D 6S 9H JD QS		

		helen wins 5 times and loses 3 times, with 44 chips.
		4C 4D 10C 10H 10S

		tony wins 2 times and loses 8 times, with 7 chips.
		JC JS QD QH AS

		jennie wins 1 times and loses 8 times, with 14 chips.
		6D 6S 9H JD QS

		Want to play a new game? Answer yes to start a new game. Enter anything else will exit the program.
		------------------------------------------------------------------------------------------------------
Case 4:		Here we start a new game and to see some special cases occured

		Command: Lab4 SevenCardStud jennie tony helen

		Program outputs:
		------------------------------------------------------------------------------------------------------
		jennie
		added
		tony
		added
		helen 
		added

		tony: * * 3D
		helen: * * 6D
		jennie: * * 4S
		
		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		bet_2_chips(input)
		Cumulative bet is now 2

		helen: Enter the action you want to take: raise_1_chip, raise_2_chips, call, or fold
		raise_1_chip(input)
		Cumulative bet is now 3

		jennie: Enter the action you want to take: raise_1_chip, raise_2_chips, call, or fold
		fold(input)
		Cumulative bet is now 3

		tony: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)

		Cumulative bet is now 3

		tony: * * 3D 3S
		helen: * * 6D 6S
		
		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		bet_1_chip(input)
		Cumulative bet is now 1

		helen: Enter the action you want to take: raise_1_chip, raise_2_chips, call, or fold
		raise_2_chips(input)
		Cumulative bet is now 3	

		tony: you can raise_1_chip, raise_2_chips, call, or fold
		call(input)
		You have only 2 chips left. All will be pushed into the pot. 
		You can stay in the game until the round is over.

		tony: * * 3D 3S KS
		helen: * * 6D 6S 7H

		tony: You have run out of chips! But you can remain in the game to see if you can win the pot!
	
		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: * * 3D 3S KS QD
		helen: * * 6D 6S 7H 6H

		tony: You have run out of chips! But you can remain in the game to see if you can win the pot!
	
		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: * * 3D 3S KS QD *
		helen: * * 6D 6S 7H 6H *

		tony: You have run out of chips! But you can remain in the game to see if you can win the pot!
	
		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		tony: 2S 3D 3S JH QD KS AD
		Best is 3D 3S QD KS AD

		helen: 5D 6C 6D 6H 6S 7H 10S
		Best is 6C 6D 6H 6S 10S

		helen wins 6 times and loses 3 times, with 52 chips.
		6C 6D 6H 6S 10S

		tony wins 2 times and loses 9 times, with 0 chips.
		3D 3S QD KS AD

		jennie wins 1 times and loses 9 times, with 13 chips.

		tony has run out of chips! To reset chips, enter reset. To leave the game, enter leave.
		reset(input)

		Want to play a new game? Answer yes to start a new game. Enter anything else will exit the program.
		yes(input)
		Which game? FiveCardDraw or SevenCardStud
		FiveCardDraw(input)
		Enter the name of players, seperated by space. You should have at least 2 players to start the game.
		When you finish, enter n.
		Like: jennie tony helen n
		jennie tony helen 
		n
		
		tony: 3C 5S 7S 9H KC
		helen: 2H 5D 8D JS KH
		jennie: 3S 5H 6C 8C QC

		tony: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		fold(input)
		Cumulative bet is now 0

		helen: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		fold(input)
		Cumulative bet is now 0
	
		jennie: Enter the action you want to take: bet_1_chip, bet_2_chips, check, or fold
		check(input)
		Cumulative bet is now 0

		jennie wins 2 times and loses 9 times, with 15 chips.
		3S 5H 6C 8C QC

		tony wins 2 times and loses 10 times, with 19 chips.

		helen wins 6 times and loses 4 times, with 51 chips.