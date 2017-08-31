#include <iostream>
#include <chrono>

#include <stdlib.h>

#include <unordered_set>
#include <tuple>
#include <vector>

#define GRID_SIZE 15
#define GRID_SIZE_M_1 14

enum Player {
  PLAYER_0 = 0,
  AI = 1,
};
int game_turn = 0;
int g_count = 0;
// int turn = 0;
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
    for(auto i_aux = i, j_aux = 0; i_aux > -1; --i_aux, ++j_aux) {
      diagonal1 = 0;
      for(auto i_sequence = i_aux, j_sequence = j_aux, count = 0;
               count < 5; --i_sequence, ++j_sequence, ++count) {
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
    for(auto i_aux = 14, j_aux = j; j_aux < GRID_SIZE; --i_aux, ++j_aux){
      diagonal1 = 0;
      for(auto i_sequence = i_aux, j_sequence = j_aux, count = 0;
               count < 5; --i_sequence, ++j_sequence, ++count) {
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
    for(auto i_aux = 0, j_aux = j; j_aux < GRID_SIZE; ++i_aux, ++j_aux){
      diagonal2 = 0;
      for(auto i_sequence = i_aux, j_sequence = j_aux, count = 0;
               count < 5; ++i_sequence, ++j_sequence, ++count) {
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
    for(auto i_aux = i, j_aux = 0; i_aux < GRID_SIZE; ++i_aux, ++j_aux){
      diagonal2 = 0;
      for(auto i_sequence = i_aux, j_sequence = j_aux, count = 0;
               count < 5; ++i_sequence, ++j_sequence, ++count) {
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
  if(check_winner(PLAYER_0))
    return true;
  if(check_winner(AI))
    return true;

  //Search for blank spaces
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(grid[i][j] == -1)
        return false;
    }
  }
  return true;
}

void populate_grid()
{
  for(auto i = 0; i < 15; ++i)
    for(auto j = 0; j < 15; ++j) {
      grid[i][j] = -1;
    }
}

void evaluate_sequence(int& n_unities_open, int&	n_doubles_open,
		int& n_triples_open, int& n_quadruples_open, int& n_quintuples,
		int sequence, int n_opens)
{
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
		default:
			if(sequence > 4 && sequence < 10)
				n_quintuples++;
			break;
	}
}

void treats_sequence(const int i, const int j, int turn, int& sequence, int& n_opens,
		int& last_position, int& n_unities_open, int& n_doubles_open,
		int& n_triples_open, int& n_quadruples_open, int& n_quintuples, bool reached_grid_limit)
{

	if(grid[i][j] == turn){
		sequence++;
		if(last_position == -1)
			n_opens++;
		if(reached_grid_limit){
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

int evaluate(int (&grid)[GRID_SIZE][GRID_SIZE], int turn, int depth)
{
	int n_unities_open = 0,
		n_doubles_open = 0,
		n_triples_open = 0,
		n_quadruples_open = 0,
		n_quintuples = 0,
		sequence = 0,
		last_position = turn == 0 ? 1 : 0,
		n_opens;
	bool reached_grid_limit;

	//HORIZONTAL GRADE
	for (int i = 0; i < GRID_SIZE; ++i) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int j = 0; j < GRID_SIZE; ++j) {
			reached_grid_limit = j == GRID_SIZE - 1;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	//VERTICAL GRADE
	for (int j = 0; j < GRID_SIZE; ++j) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = 0; i < GRID_SIZE; ++i) {
			reached_grid_limit = i == GRID_SIZE - 1;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	//UPPER LEFT TO LOWER RIGHT GRADE {(0, 14)}, {(0, 13), (1, 14)} ...
	for (int diagonal = GRID_SIZE - 1; diagonal > -1; --diagonal) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = 0, j = diagonal; j < GRID_SIZE; ++i, ++j) {
			reached_grid_limit = j == GRID_SIZE - 1;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	for (int diagonal = 1; diagonal < GRID_SIZE; ++diagonal) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = diagonal, j = 0; i < GRID_SIZE; ++i, ++j) {
			reached_grid_limit = i == GRID_SIZE - 1;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	//UPPER RIGHT TO LOWER LEFT GRADE {(0, 0)}, {(0, 1), (1, 0)}, {(0, 2), (1, 1), (2, 0)} ...
	for (int diagonal = 0; diagonal < GRID_SIZE; ++diagonal) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = 0, j = diagonal; j > -1; ++i, --j) {
			reached_grid_limit = j == 0;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	for (int diagonal = 1; diagonal < GRID_SIZE; ++diagonal) {
		n_opens = 0;
		sequence = 0;
		last_position = turn == 0 ? 1 : 0;
		for (int i = diagonal, j = GRID_SIZE - 1; i < GRID_SIZE; ++i, --j) {
			reached_grid_limit = i == 0;
			treats_sequence(i, j, turn, sequence, n_opens, last_position, n_unities_open,
					n_doubles_open, n_triples_open, n_quadruples_open, n_quintuples, reached_grid_limit);
		}
	}

	return (n_unities_open + 113*n_doubles_open + 113*100*n_triples_open + 113*100*96*n_quadruples_open + 113*100*96*70*n_quintuples);
}

void treats_sequence_incremental(int& add_to_grade, int* sequence, int seq_size, int play_position, int turn){
	int n_unities_open = 0,
		n_doubles_open = 0,
		n_triples_open = 0,
		n_quadruples_open = 0,
		n_quintuples = 0,
		left_sequence  = 0,
		right_sequence = 0,
		left_sequence_owner,
		right_sequence_owner,
		n_opens,
		n_opens_around = 0,
		seq_start = play_position,
		seq_end = play_position;

	if(play_position == 0){
		left_sequence_owner = !turn;
		right_sequence_owner = sequence[play_position + 1];
	}
	else if(play_position == seq_size - 1){
		left_sequence_owner = sequence[play_position - 1];
		right_sequence_owner = !turn;
	} else {
		left_sequence_owner = sequence[play_position - 1];
		right_sequence_owner = sequence[play_position + 1];
	}

	//looking left sequence
	n_opens = 1;
	for (int i = play_position - 1; i > -1 ; --i) {
		if(sequence[i] != left_sequence_owner || sequence[i] == -1){
			if(sequence[i] == -1){
				n_opens++;
				n_opens_around++;
			}
			break;
		}
		left_sequence++;
	}

	if(left_sequence_owner == turn)
		seq_start = play_position - left_sequence;

	if(left_sequence > 0){
		if(left_sequence_owner == !turn){
			evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open,
					n_quadruples_open, n_quintuples, left_sequence, 1);
		} else if(left_sequence_owner == turn){
			evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open,
					n_quadruples_open, n_quintuples, left_sequence, -n_opens);
		}
	}

	n_opens = 1;
	for (int i = play_position + 1; i < seq_size; ++i){
		if(sequence[i] != right_sequence_owner || sequence[i] == -1){
			if(sequence[i] == -1){
				n_opens++;
				n_opens_around++;
			}
			break;
		}
		right_sequence++;
	}

	if(right_sequence_owner == turn)
		seq_end = play_position + right_sequence;

	if(right_sequence > 0){
		if(right_sequence_owner == !turn){
			evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open,
				n_quadruples_open, n_quintuples, right_sequence, 1);
		} else if(right_sequence_owner == turn){
			evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open,
					n_quadruples_open, n_quintuples, left_sequence, -n_opens);
		}
	}

	evaluate_sequence(n_unities_open, n_doubles_open, n_triples_open,
			n_quadruples_open, n_quintuples, seq_end - seq_start + 1, n_opens_around);
	add_to_grade += (n_unities_open + 113*n_doubles_open +
			113*100*n_triples_open + 113*100*96*n_quadruples_open + 113*100*96*70*n_quintuples);
}

int evaluate_incremental(int x, int y, int (&grid)[GRID_SIZE][GRID_SIZE], int turn){
	int	start_x,
		end_x,
		start_y,
		end_y,
		*sequence,
		add_to_grade = 0;


	start_x = (x - 5) < 0 ? 0 : x - 5;
	end_x = (x + 5) > 14 ? 14 : x + 5;
	start_y = (y - 5) < 0 ? 0 : y - 5;
	end_y = (y + 5) > 14 ? 14 : y + 5;

	//vertical sequence
	sequence = new int[end_x - start_x + 1];
	for (int i = start_x, j = 0; i < end_x + 1; ++i, j++) {
		sequence[j] = grid[i][y];
	}
	treats_sequence_incremental(add_to_grade, sequence, end_x - start_x + 1, x - start_x,turn);
	delete sequence;

	//horizontal sequence
	sequence = new int[end_y - start_y + 1];
	for (int i = start_y, j = 0; i < end_y + 1; ++i, j++) {
		sequence[j] = grid[x][i];
	}
	treats_sequence_incremental(add_to_grade, sequence, end_y - start_y + 1, y - start_y,turn);
	delete sequence;

	start_x = x - 5;
	start_y = y - 5;
	end_x = x + 5;
	end_y = y + 5;
	while(start_x < 0 || start_y < 0){
		start_x++;
		start_y++;
	}
	while(end_x > GRID_SIZE - 1 || end_y > GRID_SIZE - 1){
		end_x--;
		end_y--;
	}

	sequence = new int[end_x - start_x + 1];
	for (int i = start_x, j = start_y, k = 0; i < end_x + 1; ++i, ++j, ++k) {
		sequence[k] = grid[i][j];
	}
	treats_sequence_incremental(add_to_grade, sequence, end_x - start_x + 1, x - start_x, turn);
	delete sequence;

	start_x = x + 5;
	start_y = y - 5;
	end_x = x - 5;
	end_y = y + 5;
	while(start_x > GRID_SIZE - 1 || start_y < 0){
		start_x--;
		start_y++;
	}
	while(end_x < 0 || end_y > GRID_SIZE - 1){
		end_x++;
		end_y--;
	}

	sequence = new int[end_y - start_y + 1];
	for (int i = start_x, j = start_y, k = 0; i > end_x - 1; --i, ++j, ++k) {
		sequence[k] = grid[i][j];
	}
	treats_sequence_incremental(add_to_grade, sequence, end_y - start_y + 1, y - start_y, turn);
	delete sequence;

	return add_to_grade;
}

void print_grid(const int (&array)[GRID_SIZE][GRID_SIZE])
{

  std::string print = "";
  for(auto i = 0; i < 15; ++i){
    for(auto j = 0; j < 15; ++j) {
      if(array[i][j] == -1){
        print += "| - ";
      } else {
        print += "| " + std::to_string(array[i][j]) + " ";
      }
    }
    print += "\n";
  }
  std::cout << print << std::endl;
}

int max_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta, int last_grade);

int min_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta, int last_grade)
{
  int new_grade;
  if(depth == 0 || game_over()) {
    // std::cout << "minevaluate" << std::endl;
    //return evaluate(state, game_turn, 1) - evaluate(state, !game_turn, 1);
	/*int old_way = evaluate(state, game_turn, 1) - evaluate(state, !game_turn, 1);
	if(old_way != last_grade)
		new_grade = 20;*/
	return last_grade;
  }

  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
    	new_grade = last_grade;
        // std::cout << "min = [" << i << "][" << j << "]" << std::endl;
        state[i][j] = game_turn;
        new_grade += evaluate_incremental(i, j, state, game_turn);
        auto temp_score = max_search(state, depth-1, alpha, beta, new_grade);
        // std::cout << temp_score << std::endl;
        if(temp_score > alpha)
          alpha = temp_score;

        if(alpha >= beta) {
          state[i][j] = -1;
          return beta;
        }

        state[i][j] = -1;
      }
    }
  }
  return alpha;
}

int max_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta, int last_grade)
{
  int new_grade;

  if(depth == 0 || game_over()) {
    // std::cout << "maxevaluate" << std::endl;
    //return evaluate(state, game_turn, 1) - evaluate(state, !game_turn, 1);
	/*int old_way = evaluate(state, game_turn, 1) - evaluate(state, !game_turn, 1);
	if(old_way != last_grade)
		new_grade = 20;*/
	return last_grade;
  }
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
    	new_grade = last_grade;
        // std::cout << "max = [" << i << "][" << j << "]" << std::endl;
        state[i][j] = !game_turn;
        new_grade -= evaluate_incremental(i, j, state, !game_turn);
        auto temp_score = min_search(state, depth-1, alpha, beta, new_grade);
        // std::cout << temp_score << std::endl;
        if(temp_score < beta)
          beta = temp_score;

        if(beta <= alpha) {
          state[i][j] = -1;
          return alpha;
        }
        state[i][j] = -1;
      }
    }
  }
  return beta;
}

std::tuple<int,int> minimax(int (&state)[GRID_SIZE][GRID_SIZE],int depth)
{
  std::tuple<int,int> best_move;
  auto alpha = INT32_MIN;
  auto beta = INT32_MAX;
  int new_grade = 0,
      initial_grade = evaluate(state, game_turn, depth);

  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
        // std::cout << "minimax = [" << i << "][" << j << "]" << std::endl;
    	new_grade = initial_grade;
        state[i][j] = game_turn;
        new_grade += evaluate_incremental(i, j, state, game_turn);
        auto temp_score = max_search(state, depth-1, alpha, beta, new_grade);
        // std::cout << temp_score << std::endl;
        if(temp_score > alpha) {
          alpha = temp_score;
          std::get<0>(best_move) = i;
          std::get<1>(best_move) = j;
          // std::cout << "i = " << std::get<0>(best_move) << std::endl;
          // std::cout << "j = " << std::get<1>(best_move) << std::endl;
        }
        state[i][j] = -1;
      }
    }
  }
  return best_move;
}

std::tuple<int,int> teste()
{
  return std::tuple<int, int>(0,5);
}


void game_core(){
  int turno = 0;
  print_grid(grid);
  while(turno < 2){
	    std::tuple<int,int> play = minimax(grid, 2);
	    grid[std::get<0>(play)][std::get<1>(play)] = game_turn;
	    if (check_winner(game_turn))
	      break;
	    game_turn = game_turn == 0 ? 1:0;
	    system("clear");
	    print_grid(grid);
	    turno++;
  }
  while(true){
    std::tuple<int,int> play = minimax(grid, 2);
    grid[std::get<0>(play)][std::get<1>(play)] = game_turn;
    if (check_winner(game_turn))
      break;
    game_turn = game_turn == 0 ? 1:0;
    system("clear");
    print_grid(grid);
  }
  system("clear");
  print_grid(grid);
}

int main()
{
  // ------GRID INIT------------
  populate_grid();

  // for(auto i = 0; i < 3; ++i) {
  //   for(auto j = 0; j < 3; ++j) {
  //       grid[i][j] = -1;
  //     }
  // }
  // grid[0][0] = 0;
  // grid[2][2] = 0;
  // // ---------------------------

  // std::cout << std::boolalpha << std::endl;

  // auto t_start = std::chrono::high_resolution_clock::now();

  // auto tuple = minimax(grid, 4);
  // std::cout <<  "\ni = "<< std::get<0>(tuple) << std::endl
  //           <<  "j = "<< std::get<1>(tuple) << std::endl;

  // std::cout <<  "GRADE = " << std::abs(evaluate(grid, AI,1) - evaluate(grid, PLAYER_0,1)) << std::endl;
  // std::cout <<  "GRADE_AI = " << evaluate(grid, AI,1) << std::endl;
  // std::cout <<  "GRADE_P0 = " << evaluate(grid, PLAYER_0,1) << std::endl;
  // std::cout << g_count << std::endl;
  // auto t_end = std::chrono::high_resolution_clock::now();

  // print_grid(grid);
  // std::cout << "grid: "
  //           << std::chrono::duration<double, std::milli>(t_end-t_start).count()
  //           << " ms\n";

  game_core();
  /*int last_grade = 0;
  int x, y, value;
  while(true){
	std::cin >> x;
	std::cin >> y;
	grid[x][y] = game_turn;
    if (check_winner(game_turn))
      break;
    if(game_turn == 0)
    	last_grade += evaluate_incremental(x, y, grid, game_turn);
    else
    	last_grade -= evaluate_incremental(x, y, grid, game_turn);
    game_turn = game_turn == 0 ? 1:0;
    system("clear");
    print_grid(grid);
    std::cout << last_grade << std::endl;
  }*/

}
