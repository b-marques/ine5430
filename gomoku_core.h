#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include <gtkmm.h>
#include <unordered_set>
#include <iterator>
#include "gomoku_play.h"

class GomokuCore
{
public:
  GomokuCore();
  ~GomokuCore();
  void restart();
  GomokuPlay find_squares();

private:
  int grid[15][15];
  int player;
  std::unordered_set <GomokuPlay> p0_plays;
  std::unordered_set <GomokuPlay> p1_plays;
};

#endif // GOMOKU_CORE_H
