/*
 * action.h
 *
 * 2015/9/4
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <vector>
#include <map>
#include <string>
using namespace std;

enum action_t { LABOR, CONSUME, DEPOSIT, WITHDRAW, INVEST, DIVEST, LAST };

class Action {
 private:
  static map<action_t, string> makeActionTypes();
  static map<action_t, int> makeCostTypes();
  static map<action_t, int> makePayoutTypes();

 public:
  static map<action_t, string> actionTypes;
  static map<action_t, int> costTypes;
  static map<action_t, int> payoutTypes;

  static const bool checkAction(const action_t action, const int accBalanace);
};
