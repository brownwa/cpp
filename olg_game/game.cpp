/*
 * game.cpp
 *
 * 2015/9/1
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <iostream>
#include <stdio.h>
#include "game.h"
// Included from game.h
//   #include <exception>
//   using namespace std;

int Game::_numGames = 0;

Game::Game(const int defaultPlayers, const int defaultCash, const double defaultRates[]) {
  _numGames++;
  if(_numGames > 1) {
    throw game_singleton_err();
  }
}

void Game::addPlayer(const Player newPlayer) {
  _playerV.push_back(newPlayer);
}

void Game::askPlayer(const int pIndex) {
  if(pIndex == 0) {
    _playerV[0].askAI(_turn, _maxTurns);

    return;
  }

  cout << "Player " << pIndex << ": " << _playerV[pIndex].getName() << endl;
  _playerV[pIndex].showPortfolio();

  int pBalance = 0;
  action_t pAction = LAST;
  string choice = "none";
  while( (choice == "none") && (_turn < _maxTurns) ) {

    // List player actions
    cout << "Choose a player action (cost/payout):" << endl;
    for(size_t i = LABOR; i != LAST; ++i ) {
      cout << Action::actionTypes[ static_cast<action_t>(i) ] << " \t";
    }
    cout << endl;

    // List action costs and payouts
    for(size_t i = LABOR; i != LAST; ++i) {
      cout << "( $" << Action::costTypes[ static_cast<action_t>(i) ];
      cout << " / $" << Action::payoutTypes[ static_cast<action_t>(i) ] << " )   \t";
    }
    cout << endl;

    cout << endl << "Action: ";
    cin >> choice;

    if( choice.front() == 'l' || choice.front() == 'L' ) {
      pAction = LABOR;
      pBalance = _playerV[pIndex].getCash();
      break;

    } else if( choice.front() == 'c' || choice.front() == 'C' ) {
      pAction = CONSUME;
      pBalance = _playerV[pIndex].getCash();
      break;

    } else if( choice.front() == 'd' || choice.front() == 'D' ) {
      pAction = DEPOSIT;
      pBalance = _playerV[pIndex].getCash();
      break;

    } else if( choice.front() == 'w' || choice.front() == 'W' ) {
      pAction = WITHDRAW;

      // Savings account is index 0
      pBalance = static_cast<int>( _playerV[pIndex].getPortfolio()->getAccList()[0].getBalance() );
      break;

    } else if( choice.front() == 'i' || choice.front() == 'I' ) {
      pAction = INVEST;
      pBalance = _playerV[pIndex].getCash();
      break;

    } else if( choice.front() == 'v' || choice.front() == 'V' ) {
      pAction = DIVEST;

      // Investment account is index 1
      pBalance = static_cast<int>( _playerV[pIndex].getPortfolio()->getAccList()[1].getBalance() );
      break;

    } else if( choice.front() == 's' || choice.front() == 'S' ) {
      pAction = LAST; // Skip a turn
      break;

    } else {
      cout << "Invalid choice" << endl;
      choice = "none";
    }

  }
   
  cout << "You chose to " << Action::actionTypes[pAction] << endl;
  
  if( Action::checkAction(pAction, pBalance) == true ) {
    _playerV[pIndex].doAction(pAction);
  } else {
    cout << "You don't have enough money to " << Action::actionTypes[pAction] << ", ";
    cout << "(s)kipping turn" << endl;
    choice = "none";
  }
  cout << endl;

  // Accrue interest
  _playerV[pIndex].updateAccounts();
}
