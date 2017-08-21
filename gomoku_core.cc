#include "gomoku_core.h"
#define gridSize 15

GomokuCore* GomokuCore::_instance = nullptr;

GomokuCore::GomokuCore()
: _player_turn(P1),
  _game_state(NEW_GAME)
{
  _player[0] = GomokuPlayer();
  _player[1] = GomokuPlayer();
  clearGrid();
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
  clearGrid();
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
  updateGrid(x, y);
  return true;
}

bool GomokuCore::have_winner(int x, int y)
{
	SeqGap *seq = sequenceGap(x, y, 5);
	if(seq->exists){
		_game_state = END_GAME;
		delete seq;
		return true;
	} else{
		delete seq;
		return false;
	}
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

SeqGap* GomokuCore::sequenceGap(int x, int y, int seqSize) {
	std::string horizontal = "", vertical = "",
			diagonal1 = "", diagonal2 = "", winSequence = "",
			_player_turn_str;
	int startX, endX, startY, endY, horiPos, vertPos, delta;
	SeqGap *gap = new SeqGap;

	*gap = {false, x, y, x, y};
	_player_turn_str = std::to_string(_player_turn);
	for (int i = 0; i < seqSize; ++i) {
		winSequence += _player_turn_str;
	}

	delta = seqSize - 1;
	startX = (x - delta) < 0 ? 0 : x - delta;
	endX = (x + delta) > 14 ? 14 : x + delta;
	startY = (y - delta) < 0 ? 0 : y - delta;
	endY = (y + delta) > 14 ? 14 : y + delta;

	for (int i = startY; i < endY + 1; ++i) {
		horizontal += _grid[x][i];
	}

	for (int i = startX; i < endX + 1; ++i) {
		vertical += _grid[i][y];
	}

	horiPos = horizontal.find(winSequence, 0);
	vertPos = vertical.find(winSequence, 0);
	if(horiPos != (int) horizontal.npos){
		gap->exists = true;
		gap->y1 = startY + horiPos;
		gap->y2 = gap->y1 + delta;
	} else if(vertPos != (int) vertical.npos){
		gap->exists = true;
		gap->x1 = startX + vertPos;
		gap->x2 = gap->x1 + delta;
	}
	return gap;
}

void GomokuCore::updateGrid(int x, int y) {
	_grid[x][y] = std::to_string(_player_turn);
}

void GomokuCore::clearGrid() {
	  for (int i = 0; i < gridSize; ++i) {
		  for (int j = 0; j < gridSize; ++j) {
			_grid[i][j] = " ";
		}
	  }
}
