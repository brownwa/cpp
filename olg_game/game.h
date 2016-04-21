/*
 * game.h
 *
 * 2015/9/1
 * Waheed Brown
 *
 * OLG - Overlapping Generations Game
 */

#include <exception>
#include "player.h"
// Included in player.h
//   #include <vector>
//   #include <map>
//   #include <string>
//   using namespace std;


class Game {
 private:
  static int _numGames;
  int _turn;
  int _maxTurns;
  vector<Player> _playerV;

 public:
  Game(const int defaultPlayers, const int defaultCash, const double defaultRates[]);
  const int getTurn() const { return _turn; }
  void setTurn(const int newTurn) { _turn = newTurn; }
  const int getMaxTurns() const { return _maxTurns; }
  void setMaxTurns(const int newMaxTurns) { _maxTurns = newMaxTurns; }
  void addPlayer(const Player newPlayer);
  void askPlayer(const int pIndex);
};

struct game_singleton_err : public exception {
  const char * what () const throw () {
    return "Game already exists";
  }
};
