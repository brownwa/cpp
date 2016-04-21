/*
 * olg.cpp
 *
 * 2015/9/3
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <iostream>
#include "game.h"

int main() {

  // New Game
  cout << endl << "Welcome to OLG!" << endl << endl;
  cout << "RULES: " << "OLG is a turn based game where you try to maximize your lifetime welfare." << endl;
  cout << "Make as much as you can but whoever consumes the most wins!" << endl;
  cout << endl << "1 player competes against the AI, named Peter Diamond" << endl;

  string newPlayer;
  cout << "Please enter the name of the human player: ";
  cin >> newPlayer;
  cout << endl;

  try { // Ensure that Game is a singleton
    int numPlayers = 1; // 1 human player
    int sCash = 10; // Default amount of starting cash
    double sRates[2] = {1.01, 1.04}; // 1% interest savings, 4% returns investments
    Game newGame(numPlayers, sCash, sRates);
    newGame.setMaxTurns(30);
    int turn;
    
    //    // Create AI and human players
    Player gameAI;
    Player human;
    gameAI.configPlayer("Peter Diamond", sCash, sRates);
    human.configPlayer(newPlayer, sCash, sRates);
    newGame.addPlayer(gameAI);
    newGame.addPlayer(human);
    newGame.setTurn(0);

    // The game loop
    while( newGame.getTurn() < newGame.getMaxTurns() ) {
      turn = newGame.getTurn();
      cout << "--- TURN " << (turn + 1) << " ---" << endl << endl;
  
      // Player action
      for(size_t i = 0; i < (numPlayers + 1); ++i ) {
	newGame.askPlayer(i);
	if(i < numPlayers) { cout << "---" << endl << endl; }
      }
      newGame.setTurn( turn + 1 );
    }
  } catch (exception &e) {
    cout << "Exception: " << e.what() << endl;
  }
  
  cout << "Thank you for playing, goodbye." << endl;
  
  return 0;
}
