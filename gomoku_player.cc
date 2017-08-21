#include "gomoku_player.h"

GomokuPlayer::GomokuPlayer()
: _player_type(HUMAN)
{}

GomokuPlayer::~GomokuPlayer()
{}

void GomokuPlayer::play(int x, int y)
{
  _plays.insert(GomokuPlay(x,y));
}

bool GomokuPlayer::already_played(int x, int y)
{
  auto aux = _plays.find(GomokuPlay(x,y));
  
  if(aux != _plays.end())
    return true;

  return false;
}

std::unordered_set<GomokuPlay> GomokuPlayer::plays()
{
  return _plays;
}

void GomokuPlayer::clear_plays()
{
  _plays.clear();
}