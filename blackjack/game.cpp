/*
 * game.cpp
 *
 * 2015/1/28
 * Waheed Brown
 *
 * Final Project
 * MIT6_096IAP11_project.pdf
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
// Included from game.h
//   #include <exception>
//   #include card.h
//   using namespace std;

Player::Player(const Player &p) {
  name = p.name;
  hand = p.hand;
  score = p.score;
}

void Player::showHand() const {
  for( vector<Card>::const_iterator it = hand.begin();
       it != hand.end();
       ++it ) {
    it->showCard();
    cout << '\t';
  }
}

// From cards.h
//
// enum pip_t {ACE_LOW = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6,
// 	    SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 110,
// 	    QUEEN = 210, KING = 310, ACE = 11};
//
// Therefore use modulo 10 to filter out pips >= 10
const int Player::calcHand() const {
  int total = 0;
  //  pip_t *pPtr = NULL;
  for( vector<Card>::const_iterator it = hand.begin();
       it != hand.end();
       ++it ) {
    const pip_t *pPtr = it->getNumber();

    // Use modulo 10 to filter out pips >= 10
    total += int( *(pPtr) ) % 10;
    if ( ( *(pPtr) == TEN ) || 
	 ( *(pPtr) == JACK ) ||
	 ( *(pPtr) == QUEEN ) || 
	 ( *(pPtr) == KING ) || 
	 ( *(pPtr) == ACE ) ) {
      total += 10;
    }
  }

  return total;
}

int Game::numGames = 0;

Game::Game(const int newPlayers) {
  numGames++;
  if(numGames > 1) {
    throw game_singleton_err();
  }

  srand( time(NULL) );
  numPlayers = 0;
  playerList = new Player[newPlayers + 1 /* the bank */];
  addPlayer("Bank");
 }

Game::~Game() {
  delete[] playerList;
}

void Game::addPlayer(const string playerName) {
   playerList[numPlayers++].setName(playerName);
}

void Game::showPlayers() const {
  cout << playerList[0].getName() << endl; // the bank
  for(int i = 1; i < numPlayers; ++i)
    cout << "Player " << i << ": " << playerList[i].getName() << endl;
}

void Game::buildDeck() {
  // Iterate through the maps for pips and suits to 
  // populate the deck.
  for( map<pip_t, string>::iterator it = Card::pips.begin();
       it != Card::pips.end();
       ++it ) {
    for( map<suit_t, string>::iterator jt = Card::suits.begin();
	 jt != Card::suits.end();
	 ++jt ) {
      Card newCard(jt->first, it->first);
      gameDeck.getList().push_back(newCard);
    }
  }
}

// Randomly pulling cards out of the deck is a quick and simple
// way of "shuffling" the deck
//
void Game::dealCard(const int pIndex) {
  //  int i = ( gameDeck.getList().size() - 1 ) * ( rand() / RAND_MAX );
  int i = rand() % gameDeck.getList().size();

  //  playerList[pIndex].hit( gameDeck.getList().back() );
  //  gameDeck.getList().pop_back();
  playerList[pIndex].hit( gameDeck.getList().at(i) );
  gameDeck.getList().erase( gameDeck.getList().begin() + i );
}

void Game::showTable() const {
  cout << endl << playerList[0].getName() << ": " << endl;
  playerList[0].showHand();
  cout << endl;

  // For some reason the g++ compiler optimizes the 
  // Player array playerList in a way that breaks referencing
  // Player members. For this reason, each player must be
  // copied from the playerList heap to the stack as a player
  // in order to be referenced without causing a segmentation
  // fault when cout is called.
  Player p;
  for(int i = 1; i < numPlayers; ++i) {
    p = playerList[i];
    cout << endl << "Player " << i << ": " << p.getName();
    cout << endl;
    p.showHand();
    cout << endl;
  }
  cout << endl;
}

void Game::askPlayer(const int pIndex) {
  cout << "Player " << pIndex << ": "
       << playerList[pIndex].getName() << endl;
  playerList[pIndex].showHand();
  cout << endl;
  int total = playerList[pIndex].calcHand();
  cout << "Total: " << total << endl;

  string choice = "none";
  while( (choice == "none") && (total < 21) ) {
    cout << playerList[pIndex].getName()
	 << ", do you want to hit (h) or stand (s)? ";
    cin >> choice;

    if( choice.front() == 'h' || choice.front() == 'H' ) {
      cout << "Hit: ";
      dealCard(pIndex);
      playerList[pIndex].showHand();
      cout << endl;

      total = playerList[pIndex].calcHand();
      cout << "Total: " << total;
      if(total > 21)
	cout << " BUST!";
      else if(total == 21)
	cout << " BLACKJACK!";

      cout << endl;
      choice = "none";
    }
    else if( choice.front() == 's' || choice.front() == 'S' ) {
      cout << "Stand" << endl;
      break;
    }
    else {
      cout << "Invalid choice" << endl;
      choice = "none";
    }
  }
  playerList[pIndex].setScore(total);
  cout << endl;
}

void Game::askBank() {
  cout << playerList[0].getName() << endl;
  playerList[0].showHand();
  cout << endl;
  int total = playerList[0].calcHand();
  cout << "Total: " << total << endl;

  int highScore = 0;
  for(int i = 1; i < numPlayers /* including Bank */; ++i)
    highScore =
      ( playerList[i].getScore() >= highScore ) &&
      ( playerList[i].getScore() <= 21 ) ?
      playerList[i].getScore() : highScore;

  string choice = "none";
  while(total < 21) {
    if(total < highScore) {
      cout << "Hit: ";
      dealCard(0);
      playerList[0].showHand();
      cout << endl;
      
      total = playerList[0].calcHand();
      cout << "Total: " << total;
      if(total > 21)
	cout << " BUST!";
      else if(total == 21)
	cout << " BLACKJACK!";
      
      cout << endl;
      choice = "none";
    }
    else if(total > highScore) {
      cout << "Bank wins!" << endl;
      break;
    }
    else if(total == highScore) {
      cout << "Push (tie)" << endl;
      break;
    }
  }
  playerList[0].setScore(total);
  cout << endl;
}

void Game::checkWinners() const {
  int score;
  int bankScore = playerList[0].getScore();
  
  for(int i = 1; i < numPlayers; ++i) {
    score = playerList[i].getScore();
    cout << "Player " << i << " total: " << score << ' ';

    if(score > 21) {
      cout << "Bust!";
      cout << endl;
      continue;
    }
    else if(score == 21)
      cout << "BLACKJACK! Congratulations " << playerList[i].getName() << "! ";

    if(score == bankScore)
      cout << "Push (tie)";
    else if(score > bankScore)
      cout << "you win " << playerList[i].getName() << "!";
    else if(bankScore <= 21)
      cout << "sorry " << playerList[i].getName() << ", you lose";
    
    cout << endl;
  }
}

void Game::playAgain(const int pIndex, int *g_newPlayers) {
  cout << playerList[pIndex].getName() << ", would you like to play again? ";
  string again;
  cin >> again;

  if( ( again.front() == 'y' ) || ( again.front() == 'Y' ) )
    cout << "\tPlayer " << pIndex << " will play again, thank you";
  else {
    cout << "\tGoodbye " << playerList[pIndex].getName() << '!';
    numPlayers--;
    g_newPlayers--;
    Player *tempList = new Player[numPlayers];

    int j = 0;
    for(int i = 1; i < numPlayers; ++i) {
      j++;
      if(j == pIndex)
	continue;

      tempList[i] = playerList[j];
    }

    delete[] playerList;
    playerList = tempList;
    delete[] tempList;
  }

  cout << endl;
}
