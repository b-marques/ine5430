#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include <gtkmm.h>
#include "gomoku_player.h"

enum GameState {
  NEW_GAME = 0,
  IN_GAME,
  END_GAME,
};

enum PlayerTurn {
  P1 = 0,
  P2 = 1,
};

class GomokuCore
{
public:
  static GomokuCore* instance();
  ~GomokuCore();  

  void restart();
  void change_turn();
  bool compute_play(int x, int y);
  GomokuPlay find_squares();
  PlayerTurn player_turn();
  GameState game_state();

private:
  GomokuCore();
  static GomokuCore* _instance;
  int _grid[15][15];
  PlayerTurn _player_turn;
  GameState _game_state;
  GomokuPlayer _player[2];
};

#endif // GOMOKU_CORE_H
