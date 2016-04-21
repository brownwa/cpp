/*
 * bank.h
 *
 * 2015/9/3
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <vector>
#include <map>
#include <string>
using namespace std;

enum account_t { SAVINGS, INVESTMENT };

class Account {
 private:
  account_t _accType;
  double _balance;
  double _rate;
  static map<account_t, string> makeAccTypes();

 public:
  static map<account_t, string> accTypes;
  Account() {}
  Account(const account_t newAccType, const double newBalance, const double newRate) :
    _accType(newAccType), _balance(newBalance), _rate(newRate) {}
  const double getBalance() const { return _balance; }
  void setBalance(const double newBalance) { _balance = newBalance; }
  void updateBalance() { _balance = _balance * _rate; }
  void showBalance() const;
};

class Portfolio {
 private:
  vector<Account> _accountV;

 public:
  Portfolio() {}
  vector<Account> &getAccList() { return _accountV; }
  void showAccounts() const;
};
