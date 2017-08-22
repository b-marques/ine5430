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
  std::unordered_set<GomokuPlay> sequence_of_four(int x, int y);
  SeqGap* find_sequence(int x, int y, int seq_size);
  PlayerTurn player_turn();
  GameState game_state();

  const static int GRID_SIZE = 15;

private:
  GomokuCore();
  static GomokuCore* _instance;
  void update_grid(int x, int y);
  void fill_grid(std::string string);

  std::string _grid[GRID_SIZE][GRID_SIZE];
  PlayerTurn _player_turn;
  GameState _game_state;
  GomokuPlayer _player[2];
};

#endif // GOMOKU_CORE_H
