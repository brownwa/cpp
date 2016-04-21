/*
 * action.cpp
 *
 * 2015/9/4
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <iostream>
#include "action.h"
// Included in action.h
//   #include <vector>
//   #include <map>
//   #include <string>
//   using namespace std;

map<action_t, string> Action::makeActionTypes() {
  map<action_t, string> newActionTypes;
  newActionTypes[LABOR] = "(l)abor";
  newActionTypes[CONSUME] = "(c)onsume";
  newActionTypes[DEPOSIT] = "(d)eposit";
  newActionTypes[WITHDRAW] = "(w)ithdraw";
  newActionTypes[INVEST] = "(i)nvest";
  newActionTypes[DIVEST] = "di(v)est";
  newActionTypes[LAST] = "(s)kip";

  return newActionTypes;
}

map<action_t, int> Action::makeCostTypes() {
  map<action_t, int> newCostTypes;
  newCostTypes[LABOR] = 1;
  newCostTypes[CONSUME] = 2;
  newCostTypes[DEPOSIT] = 5;
  newCostTypes[WITHDRAW] = 0;
  newCostTypes[INVEST] = 10;
  newCostTypes[DIVEST] = 0;
  newCostTypes[LAST] = 0;

  return newCostTypes;
}

map<action_t, int> Action::makePayoutTypes() {
  map<action_t, int> newPayoutTypes;
  newPayoutTypes[LABOR] = 2;
  newPayoutTypes[CONSUME] = 1;
  newPayoutTypes[DEPOSIT] = 0;
  newPayoutTypes[WITHDRAW] = 6;
  newPayoutTypes[INVEST] = 0;
  newPayoutTypes[DIVEST] = 15;
  newPayoutTypes[LAST] = 0;

  return newPayoutTypes;
}

map<action_t, string> Action::actionTypes = Action::makeActionTypes();
map<action_t, int> Action::costTypes = Action::makeCostTypes();
map<action_t, int> Action::payoutTypes = Action::makePayoutTypes();

const bool Action::checkAction(const action_t action, const int accBalance) {
  bool valid = false;

  switch (action)
    {
    case LABOR :
      if( accBalance >= costTypes[LABOR] ) {
	valid = true;
      }
      break;
    case CONSUME :
      if( accBalance >= costTypes[CONSUME] ) {
	valid = true;
      }
      break;
    case DEPOSIT :
      if( accBalance >= costTypes[DEPOSIT] ) {
	valid = true;
      }
      break;
    case WITHDRAW :
      if( accBalance >= payoutTypes[WITHDRAW] ) {
	valid = true;
      }
      break;
    case INVEST :
      if( accBalance >= costTypes[INVEST] ) {
	valid = true;
      }
      break;
    case DIVEST :
      if( accBalance >= payoutTypes[DIVEST] ) {
	valid = true;
      }
      break;
    case LAST :
      valid = true; // Skip a turn
      break;
    default :
      valid = false;
    }

  return valid;
}
