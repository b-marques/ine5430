#include <iostream>
#include <chrono>

#include <unordered_set>
#include <tuple>
#include <vector>
#include <algorithm> //std::sort

#include "gomoku_core.h"
#define GRID_SIZE 15
#define GRID_SIZE_M_1 14
#define PLAYER_1 1
#define PLAYER_0 0

int grid[GRID_SIZE][GRID_SIZE];

bool check_winner(int player)
{
  int win_sequence = 0;
  for (int i = 0; i < 5; ++i) {
    win_sequence = (win_sequence << 1) + player;
  }
  // std::cout << win_sequence << std::endl;

  // HONRIZONTAL SEARCH
  int horizontal = 0;
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      horizontal = 0;
      for(auto s = j; s < j+5; ++s) {
        if(s > GRID_SIZE_M_1 || grid[i][s] == -1){
          horizontal = -1;
          break;
        }
        horizontal = (horizontal << 1) + grid[i][s];
      }
      if (horizontal == win_sequence)
        return true;
    }
  }

  // VERTICAL SEARCH
  int vertical;
  for(auto j = 0; j < GRID_SIZE; ++j){
    for(auto i = 0; i < GRID_SIZE; ++i) {
      vertical = 0;
      for(auto s = i; s < i+5; ++s) {
        if(s > GRID_SIZE_M_1 || grid[i][s] == -1){
          vertical = -1;
          break;
        }
        vertical = (vertical << 1) + grid[i][s];
      }
      if (vertical == win_sequence)
        return true;
    }
  }

  // DIAGONAL 1 SEARCH TOP:
  int diagonal1;
  for(auto i = 0; i < GRID_SIZE; ++i) {
    for(auto i_aux = i,
             j_aux = 0;
             i_aux > -1;
             --i_aux, ++j_aux) {
      diagonal1 = 0;
      for(auto i_sequence = i_aux,
               j_sequence = j_aux,
               count = 0;
               count < 5;
             --i_sequence, ++j_sequence, ++count) {
        if(i_sequence < 0 || grid[i_sequence][j_sequence] == -1) {
          diagonal1 = -1;
          break;
        }
        diagonal1 = (diagonal1 << 1) + grid[i_sequence][j_sequence];
      }
      if (diagonal1 == win_sequence)
        return true;
    }
  }
  // DIAGONAL SEARCH 1 BOTTOM:
  for(auto j = 1; j < GRID_SIZE; ++j) {
    for(auto i_aux = 14,
             j_aux = j;
             j_aux < GRID_SIZE;
             --i_aux, ++j_aux){

      diagonal1 = 0;
      for(auto i_sequence = i_aux,
               j_sequence = j_aux,
               count = 0;
               count < 5;
             --i_sequence, ++j_sequence, ++count) {
        if(j_sequence > GRID_SIZE_M_1 || grid[i_sequence][j_sequence] == -1){
          diagonal1 = -1;
          break;
        }
        diagonal1 = (diagonal1 << 1) + grid[i_sequence][j_sequence];
      }

      if (diagonal1 == win_sequence)
        return true;
    }
  }
  int diagonal2;
  // DIAGONAL 2 SEARCH TOP
  for(auto j = 0; j < GRID_SIZE; ++j) {
    for(auto i_aux = 0,
             j_aux = j;
             j_aux < GRID_SIZE;
             ++i_aux, ++j_aux){
      diagonal2 = 0;
      for(auto i_sequence = i_aux,
               j_sequence = j_aux,
               count = 0;
               count < 5;
             ++i_sequence, ++j_sequence, ++count) {
        if(j_sequence > GRID_SIZE_M_1 || grid[i_sequence][j_sequence] == -1){
          diagonal2 = -1;
          break;
        }
        diagonal2 = (diagonal2 << 1) + grid[i_sequence][j_sequence];

      }
      if (diagonal2 == win_sequence)
        return true;
    }
  }

  // DIAGONAL 2 SEARCH BOTTOM
  for(auto i = 1; i < GRID_SIZE; ++i) {
    for(auto i_aux = i,
             j_aux = 0;
             i_aux < GRID_SIZE;
             ++i_aux, ++j_aux){
      diagonal2 = 0;
      for(auto i_sequence = i_aux,
               j_sequence = j_aux,
               count = 0;
               count < 5;
             ++i_sequence, ++j_sequence, ++count) {
        if(i_sequence > GRID_SIZE_M_1 || grid[i_sequence][j_sequence] == -1){
          diagonal2 = -1;
          break;
        }
        diagonal2 = (diagonal2 << 1) + grid[i_sequence][j_sequence];

      }
      if (diagonal2 == win_sequence)
        return true;
    }
  }
  return false;
}

bool game_over()
{
  if(check_winner(PLAYER_0)) return true;
  if(check_winner(PLAYER_1)) return true;

  //Search for blank spaces
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(grid[i][j] == -1)
        return false;
    }
  }
  return true;
}

int evaluate(int grid[][GRID_SIZE])
{
  // if(check_winner(PLAYER_0)) return 10;
  // if(check_winner(PLAYER_1)) return -10;
  return 0;
}

//std::tuple<int,int> minimax()


void populate_grid()
{
  for(auto i = 0; i < 15; ++i)
    for(auto j = 0; j < 15; ++j) {
      grid[i][j] = -1;
    }
  for(auto i = 14, j=1; i > 9; --i, ++j)
      grid[i][j] = PLAYER_1;
      grid[14][1] = 0;

  std::string print = "";
  for(auto i = 0; i < 15; ++i){
    for(auto j = 0; j < 15; ++j) {
      print += std::to_string(grid[i][j]) + "   ";
    }
    print += "\n";
  }
  std::cout << print << std::endl;
}

void evaluate_sequence(int& n_unities_open, int&	n_doubles_open,
		int& n_triples_open, int& n_quadruples_open, int& n_quintuples,
		int sequence, int n_opens){
	switch (sequence) {
		case 1:
			n_unities_open += n_opens;
			break;
		case 2:
			n_doubles_open += n_opens;
			break;
		case 3:
			n_triples_open += n_opens;
			break;
		case 4:
			n_quadruples_open += n_opens;
			break;
		case 5:
			n_quintuples++;
			break;
		default:
			break;
	}
}

int grid_grade(int grid[GRID_SIZE][GRID_SIZE], PlayerTurn turn){
	int n_unities_open = 0,
		n_doubles_open = 0,
		n_triples_open = 0,
		n_quadruples_open = 0,
		n_quintuples = 0,
		sequence = 0,
		last_position = turn == 0 ? 1 : 0,
		n_opens;


	//HORIZONTAL GRADE
	for (int i = 0; i < GRID_SIZE; ++i) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int j = 0; j < GRID_SIZE; ++j) {
			if(grid[i][j] == turn){
				sequence++;
				if(last_position == -1)
					n_opens++;
				if(j == GRID_SIZE - 1 && n_opens > 0){
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			}
			else if(grid[i][j] == -1){
				if(sequence > 0){
					n_opens++;
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			} else {
				if(sequence > 0){
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			}
			last_position = grid[i][j];
		}
	}

	//VERTICAL GRADE
	for (int j = 0; j < GRID_SIZE; ++j) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = 0; i < GRID_SIZE; ++i) {
			if(grid[i][j] == turn){
				sequence++;
				if(last_position == -1)
					n_opens++;
				if(i == GRID_SIZE - 1 && n_opens > 0){
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			}
			else if(grid[i][j] == -1){
				if(sequence > 0){
					n_opens++;
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			} else {
				if(sequence > 0){
					evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, sequence, n_opens);
					n_opens = 0;
					sequence = 0;
				}
			}
			last_position = grid[i][j];
		}
	}

	return n_unities_open + 113*n_doubles_open + 113*100*n_triples_open + 113*100*96*n_quadruples_open + 113*100*96*70*n_quintuples;
}

int main()
{
  populate_grid();
  std::cout << std::boolalpha << std::endl;

  auto t_start = std::chrono::high_resolution_clock::now();

  std::cout << game_over() << std::endl;

  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout << "grid: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";
 
  std::cout << grid_grade(grid, P1) << std::endl;
  std::cout << grid_grade(grid, P2);
}