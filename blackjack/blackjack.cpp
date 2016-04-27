/*
 * blackjack.cpp
 *
 * 2015/1/28
 * Waheed Brown
 *
 * Blackjack
 */

#include <iostream>
#include "game.h"
// Included wiht game.h
//   #include <string>
//   using namespace std;

void roundDeal(Game *g) {
 cout << "Dealing cards, starting with player 1." << endl;
  
 for(int i = 1 /* 0 is the bank */; i < g->getNumPlayers(); ++i)
    g->dealCard(i);

 g->dealCard(0);
}

int main() {
  int newPlayers;

  // New Game
  cout << endl << "Welcome to Blackjack!" << endl;
  cout << endl << "RULES:\t" << "Aces count as 11 only" << endl;
  cout << "\tPlayers compete against the bank, not each other" << endl;
  cout << endl << "Please enter the number of players (1 to 4): ";
  cin >> newPlayers;
  
  try { // Ensure that Game is a singleton
    Game newGame(newPlayers);

    // Add Players
    string playerName;

    for(int i = 1 /* 0 is bank */; i <= newPlayers; ++i) {
      if(i <= 1)
	cout << "Enter the name of the first player: ";
      else
	cout << "Enter the name of the next player: ";
    
      cin >> playerName;
      newGame.addPlayer(playerName);
    }
    cout << endl << "This game will have the following players: " << endl;
    newGame.showPlayers();

    // The game loop
    while(true) {
      // Shuffle Cards

      // Deal Cards
      newGame.buildDeck();
      cout << endl;
      roundDeal(&newGame);
      roundDeal(&newGame);
      newGame.showTable();
    
      // Ask each players if the want to hit or stand
      for(int i = 1 /* 0 is bank */; i <= newPlayers; ++i)
	newGame.askPlayer(i);

      // Play Bank
      newGame.askBank();

      // Determin winners
      newGame.checkWinners();

      // Collect Cards
      for(int i = 0 /* bank's cards too */; i <= newPlayers; ++i)
	newGame.clearHand(i);

      // Ask play again
      cout << endl << "Would you like to play again? ";
      string newRound;
      cin >> newRound;
      if( ( newRound.front() == 'y' ) || ( newRound.front() == 'Y' ) )
	continue;
      else
	break;
    }
  }
  catch (exception &e) {
    cout << "Exception: " << e.what() << endl;
  }

  cout << "Thank you for playing, goodbye." << endl;

  return 0;
}
