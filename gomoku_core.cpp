#include "gomoku_core.h"
#include <iostream>

GomokuCore* GomokuCore::_instance = nullptr;

GomokuCore::GomokuCore()
: _player_turn(P1),
  _game_state(NEW_GAME)
{
  _player[0] = GomokuPlayer();
  _player[1] = GomokuPlayer();
  fill_grid(" ");
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
  fill_grid(" ");
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
  update_grid(x, y);

  return true;
}

bool GomokuCore::have_winner(int x, int y)
{
	SeqGap *seq = find_sequence(x, y, 5);
	if(seq->exists){
		_game_state = END_GAME;
		delete seq;
		return true;
	} else{
		delete seq;
		return false;
	}
}

std::unordered_set<GomokuPlay> GomokuCore::sequence_of_four(int x, int y)
{
  SeqGap *seq = find_sequence(x, y, 4);
  std::unordered_set<GomokuPlay> possible_plays;
  
  if(seq->exists) {
    if( seq->x1 > -1 && seq->x1 < 15 && 
        seq->y1 > -1 && seq->y1 < 15 &&
        (!_player[P1].already_played(seq->x1, seq->y1) &&
         !_player[P2].already_played(seq->x1,seq->y1))) {
          
      possible_plays.insert(GomokuPlay(seq->x1, seq->y1));
    }
        

    if(seq->x2 > -1 && seq->x2 < 15 && 
       seq->y2 > -1 && seq->y2 < 15 && 
        (!_player[P1].already_played(seq->x2,seq->y2) &&
         !_player[P2].already_played(seq->x2,seq->y2))) {

      possible_plays.insert(GomokuPlay(seq->x2, seq->y2));
    }

  }

  delete seq;
  return possible_plays;
}

SeqGap* GomokuCore::find_sequence(int x, int y, int seq_size)
{
  std::string horizontal = "",
              vertical = "",
              diagonal1 = "",
              diagonal2 = "",
              win_sequence = "",
              player_turn_str;

  int //start_x,
      //end_x,
      //start_y,
      //end_y,
      hori_pos,
      vert_pos,
      diag_pos1,
      diag_pos2;
      //delta;

  SeqGap *gap = new SeqGap;
  *gap = {false, x, y, x, y};

  player_turn_str = std::to_string(_player_turn);
  
  for (int i = 0; i < seq_size; ++i) {
    win_sequence += player_turn_str;
  }

  // delta = seq_size - 1;
  // start_x = (x - delta) < 0 ? 0 : x - delta;
  // end_x = (x + delta) > 14 ? 14 : x + delta;
  // start_y = (y - delta) < 0 ? 0 : y - delta;
  // end_y = (y + delta) > 14 ? 14 : y + delta;

  // for (int i = start_y; i < end_y + 1; ++i) {
  //   horizontal += _grid[x][i];
  // }

  // for (int i = start_x; i < end_x + 1; ++i) {
  //   vertical += _grid[i][y];
  // }

  // hori_pos = horizontal.find(win_sequence, 0);
  // vert_pos = vertical.find(win_sequence, 0);
  // if(hori_pos != (int) horizontal.npos){
  //   gap->exists = true;
  //   gap->y1 = start_y + hori_pos;
  //   gap->y2 = gap->y1 + delta;
  // } else if(vert_pos != (int) vertical.npos){
  //   gap->exists = true;
  //   gap->x1 = start_x + vert_pos;
  //   gap->x2 = gap->x1 + delta;
  // }
  // return gap;

  // HONRIZONTAL SEARCH
  for (int j = 0; j < GRID_SIZE; ++j) {
    horizontal += _grid[x][j];
  }

  hori_pos = horizontal.find(win_sequence, 0);
  if(hori_pos != (int) horizontal.npos){
    gap->exists = true;
    gap->y1 = hori_pos - 1;
    gap->y2 = hori_pos + seq_size;
    return gap;  
  }


  // VERTICAL SEARCH:
  for (int i = 0; i < GRID_SIZE; ++i) {
    vertical += _grid[i][y];
  }

  vert_pos = vertical.find(win_sequence, 0);
  if(vert_pos != (int) vertical.npos){
    gap->exists = true;
    gap->x1 = vert_pos - 1;
    gap->x2 = vert_pos + seq_size;
    return gap;  
  }

  // DIAGONAL SEARCH 1:
  int start_x, start_y;

  if(x >= y) {
    start_x = x - y;
    start_y = 0;
  } else {
    start_x = 0;
    start_y = y - x;
  }

  for(auto i = start_x, j = start_y; i < GRID_SIZE && j < GRID_SIZE ; ++i, ++j){
    diagonal1 += _grid[i][j];
  }

  diag_pos1 = diagonal1.find(win_sequence, 0);
  if(diag_pos1 != (int) diagonal1.npos){
    gap->exists = true;
    gap->x1 = start_x + diag_pos1 - 1;
    gap->y1 = start_y + diag_pos1 - 1;
    gap->x2 = gap->x1 + seq_size + 1;
    gap->y2 = gap->y1 + seq_size + 1;
    return gap;  
  }

  // DIAGONAL SEARCH 2:
  if(x + y < GRID_SIZE) {
    start_x = x + y;
    start_y = 0;
  } else {
    start_x = GRID_SIZE - 1;
    start_y = (x + y) - (GRID_SIZE-1);
  }

  for(auto i = start_x, j = start_y; i > -1 && j < GRID_SIZE; --i, ++j){
    diagonal2 += _grid[i][j];
  }

  diag_pos2 = diagonal2.find(win_sequence, 0);
  if(diag_pos2 != (int) diagonal2.npos){
    gap->exists = true;
    gap->x1 = start_x - diag_pos2 + 1;
    gap->y1 = start_y + diag_pos2 - 1;
    gap->x2 = gap->x1 - seq_size -1 ;
    gap->y2 = gap->y1 + seq_size + 1;
    return gap;  
  }

  return gap;  
}

PlayerTurn GomokuCore::player_turn()
{
  return _player_turn;
}

GameState GomokuCore::game_state()
{
  return _game_state;
}

void GomokuCore::update_grid(int x, int y) {
	_grid[x][y] = std::to_string(_player_turn);
}

void GomokuCore::fill_grid(std::string string) {
  for (int i = 0; i < GRID_SIZE; ++i) {
	  for (int j = 0; j < GRID_SIZE; ++j) {
		  _grid[i][j] = string;
	  }
  }
}

GomokuPlay GomokuCore::minimax(std::string grid[GRID_SIZE][GRID_SIZE], int depth){
  // îf(have_winner() || depth == 0)
    // return evaluate(grid);

  return GomokuPlay(0,0);
}
