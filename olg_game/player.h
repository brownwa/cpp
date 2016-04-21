/*
 * player.h
 *
 * 2015/9/5
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include "action.h"
// Included in action.h
//   #include <vector>
//   #include <map>
//   #include <string>
//   using namespace std;
#include "bank.h"

class Player {
 protected:
  string _name;
  int _cash;
  Portfolio _portfolio;
  int _consumed; // player's score

 public:
  Player() {}
  const string &getName() const { return _name; }
  const int getCash() const { return _cash; }
  Portfolio* getPortfolio() const { return const_cast<Portfolio*>(&_portfolio); }
  void configPlayer( const string cName, const int cCash, const double cRates[] );
  void addAccount(account_t newType, int newAmount, double newRate);
  void doAction(const action_t newAction);
  void updateAccounts();
  void askAI(const int t /* current turn */, const int T /* max turns */);
  const action_t makeChoice(const int t, const int T);
  void showPortfolio() const;
};
