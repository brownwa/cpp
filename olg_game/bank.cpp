/*
 * bank.cpp
 *
 * 2015/9/3
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <iostream>
#include "bank.h"
// Included in bank.h
//   #include <vector>
//   #include <map>
//   #include <string>
//   using namespace std;

map<account_t, string> Account::makeAccTypes() {
  map<account_t, string> newAccTypes;
  newAccTypes[SAVINGS] = "savings";
  newAccTypes[INVESTMENT] = "investment";

  return newAccTypes;
}
map<account_t, string> Account::accTypes = Account::makeAccTypes();

void Account::showBalance() const {
  cout << Account::accTypes[_accType] << " account balance: " << _balance;
  cout << " (" << ( (_rate - 1) * 100 ) << "% rate)" << endl;
}

void Portfolio::showAccounts() const {
  for( vector<Account>::const_iterator it = _accountV.begin();
       it != _accountV.end();
       ++it ) {
    it->showBalance();
  }
}
