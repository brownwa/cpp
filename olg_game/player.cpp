/*
 * player.cpp
 *
 * 2015/9/1
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <iostream>
#include "player.h"
// Included from player.h
//   #include "action.h"
//   #include "bank.h"
//   using namespace std;

void Player::configPlayer( const string cName, const int cCash, const double cRates[] ) {
  _name = cName;
  _cash = cCash;
  _consumed = 0;

  addAccount( SAVINGS, 0, cRates[0] );
  addAccount( INVESTMENT, 0, cRates[1] );
}

void Player::addAccount(account_t newType, int newAmount, double newRate) {
  Account newAccount(newType, newAmount, newRate);
  _portfolio.getAccList().push_back(newAccount);
}

void Player::doAction(const action_t newAction) {

  switch(newAction)
    {
    case LABOR :
      _consumed = _consumed + Action::costTypes[newAction];
      break;
    case CONSUME :
      _consumed = _consumed + Action::costTypes[newAction];
      break;
    case DEPOSIT :
      // Savings account is index 0 in portfolio's _accountV vector
      _portfolio.getAccList()[0].setBalance( _portfolio.getAccList()[0].getBalance() +
					  Action::costTypes[newAction] );
      break;
    case WITHDRAW :
      _portfolio.getAccList()[0].setBalance( _portfolio.getAccList()[0].getBalance() -
					  Action::payoutTypes[newAction] );
      break;
    case INVEST :
      // Investment account is index 1 in portfolio's _accountV vector
      _portfolio.getAccList()[1].setBalance( _portfolio.getAccList()[1].getBalance() +
					  Action::costTypes[newAction] );
      break;
    case DIVEST :
      _portfolio.getAccList()[1].setBalance( _portfolio.getAccList()[1].getBalance() -
					  Action::payoutTypes[newAction] );
      break;
    case LAST :
      // Skip a turn
      break;
    default :
      cout << "Invalid action: " << Action::actionTypes[newAction] << endl;
    }
  
  _cash = _cash + Action::payoutTypes[newAction] - Action::costTypes[newAction];
}

void Player::updateAccounts() {
  // Accrue interest
  _portfolio.getAccList()[0].updateBalance();
  _portfolio.getAccList()[1].updateBalance();
  showPortfolio();
}

void Player::showPortfolio() const {
  cout << "cash: " << _cash << endl;
  _portfolio.showAccounts();
  cout << "consumed: " << _consumed << endl << endl;
}

void Player::askAI(const int t /* current turn */, const int T /* max turns */) {
  cout << getName() << ":" << endl;
  showPortfolio();

  int aiBalance = 0;
  action_t aiAction;
  //  aiAction = makeChoice(t, T - 1); // t = { 0 ... (T - 1) }
  aiAction = makeChoice(t, T);
  switch (aiAction)
    {
    case LABOR :
      aiAction = LABOR;
      aiBalance = getCash(); // AI is always player 0
      break;
    case CONSUME :
      aiAction = CONSUME;
      aiBalance = getCash();
      break;
    case DEPOSIT :
      aiAction = DEPOSIT;
      aiBalance = getCash();
      break;
    case WITHDRAW :
      aiAction = WITHDRAW;
      // Savings account is index 0
      aiBalance = static_cast<int>( getPortfolio()->getAccList()[0].getBalance() );
      break;
    case INVEST :
      aiAction = INVEST;
      aiBalance = getCash();
      break;
    case DIVEST :
      aiAction = DIVEST;
      // Investment account is index 1
      aiBalance = static_cast<int>( getPortfolio()->getAccList()[1].getBalance() );
      break;
    default :
      aiAction = LAST; // skip a turn
    }

  cout << _name << " chose to " << Action::actionTypes[aiAction] << endl;

  if( Action::checkAction(aiAction, aiBalance) == true) {
    doAction(aiAction);
  } else {
    cout << getName() << " doesn't have enough money to " << Action::actionTypes[aiAction] << endl;
    cout << getName() << " will skip a turn" << endl;
  }
  cout << endl;

  updateAccounts(); // Accrue interest
}

const action_t Player::makeChoice(const int t, const int T)  {
  int aiSBalance = static_cast<int>( _portfolio.getAccList()[0].getBalance() );
  int aiIBalance = static_cast<int>( _portfolio.getAccList()[1].getBalance() );
  action_t aiChoice = LAST; // Skip a turn

// GAME AI
//
// Where t = {1 ... T}
// 1. If cash is > (T - t + 1),
//    then consume
// 2. Otherwise, if cash is >= const_invest + 1,
//    and total_wealth <= (T - t + 1),
//    then invest
// 3. Otherwise, if investments >= (T - t + 1) - cash,
//    and investments >= cost_divest
//    then divest
// 4. Otherwise, if cash <= (T - t + 1), then labor
// 5. Otherwise, if cash >= 2, then consume
// *NOTE: Always leave at least $1 in cash so you can labor.

  // t = {0 ... 30}, so can use (T - t) instead of (T - t + 1)
  if( _cash > (T - t) ) {
    aiChoice = CONSUME;
  } else if( ( _cash >= ( Action::costTypes[INVEST] + 1 ) ) &&
	     ( (_cash + aiSBalance + aiIBalance) <= (T - t) ) ) {
    aiChoice = INVEST;
  } else if( (aiIBalance >= (T - t) - _cash) &&
	     (aiIBalance >= Action::payoutTypes[DIVEST]) ) { // no -ve balances
    aiChoice = DIVEST;
  } else if( _cash <= (T - t) ) {
    aiChoice = LABOR;
  } else if( _cash >= 2 ) {
    aiChoice = CONSUME;
  } else {
    aiChoice = LAST; // skip a turn
  }

  return aiChoice;
}
