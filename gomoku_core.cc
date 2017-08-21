#include "gomoku_core.h"

GomokuCore* GomokuCore::_instance = nullptr;

GomokuCore::GomokuCore()
: _player_turn(P1),
  _game_state(NEW_GAME)
{
  _player[0] = GomokuPlayer();
  _player[1] = GomokuPlayer();
}

GomokuCore::~GomokuCore()
{
  delete _instance;
}

GomokuCore* GomokuCore::instance()
{
  if(_instance == nullptr)
  {
    _instance = new GomokuCore();
  }
  return _instance;
}

void GomokuCore::restart()
{
  _game_state = NEW_GAME;
  _player_turn = P1;
  _player[P1].clear_plays();
  _player[P2].clear_plays();
}

void GomokuCore::change_turn()
{
  if(_game_state == NEW_GAME) {
    _game_state = IN_GAME;
  }

  _player_turn = _player_turn == P1 ? P2 : P1;
}

bool GomokuCore::compute_play(int x, int y)
{
  if(_player[P1].already_played(x, y) || _player[P2].already_played(x,y))
    return false;

  _player[_player_turn].play(x, y);
  return true;
}

bool GomokuCore::have_winner()
{
  // if(victory_condition) {
  //   _game_state = END_GAME;
  //   return true;
  // }
  return false;
}

GomokuPlay GomokuCore::find_squares()
{
	return GomokuPlay(0,0);
}

PlayerTurn GomokuCore::player_turn()
{
  return _player_turn;
}

GameState GomokuCore::game_state()
{
  return _game_state;
}