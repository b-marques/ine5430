#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include "gomoku_player.h"

struct SeqGap{
	bool exists;
	int x1, y1, x2, y2;
};

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
  bool have_winner(int x, int y);
  GomokuPlay find_squares();
  PlayerTurn player_turn();
  GameState game_state();
  SeqGap* sequenceGap(int x, int y, int seqSize);

private:
  GomokuCore();
  static GomokuCore* _instance;
  std::string _grid[15][15];
  PlayerTurn _player_turn;
  GameState _game_state;
  GomokuPlayer _player[2];
  void updateGrid(int x, int y);
  void clearGrid();
};

#endif // GOMOKU_CORE_H
