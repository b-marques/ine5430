#include <iostream>
#include <chrono>

#include <unordered_set>
#include <tuple>
#include <vector>

#define GRID_SIZE 15
#define GRID_SIZE_M_1 14

enum Player {
  PLAYER_0 = 0,
  AI = 1,
};
int count = 0;
int turn = 0;
int grid[GRID_SIZE][GRID_SIZE];

void evaluate_sequence(int& n_unities_open, int&  n_doubles_open,
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

int evaluate(int grid[GRID_SIZE][GRID_SIZE], Player player)
{
  int n_unities_open = 0,
      n_doubles_open = 0,
      n_triples_open = 0,
      n_quadruples_open = 0,
      n_quintuples = 0,
      sequence = 0,
      last_position = player == 0 ? 1 : 0,
      n_opens;


  //HORIZONTAL GRADE
  for (int i = 0; i < GRID_SIZE; ++i) {
    n_opens = 0;
    sequence = 0;
    last_position = player == 0 ? 1 : 0;
    for (int j = 0; j < GRID_SIZE; ++j) {
      if(grid[i][j] == player){
        sequence++;
        if(last_position == -1)
          n_opens++;
        if(j == GRID_SIZE - 1){
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
    last_position = player == 0 ? 1 : 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
      if(grid[i][j] == player){
        sequence++;
        if(last_position == -1)
          n_opens++;
        if(i == GRID_SIZE - 1){
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


bool check_winner(int Player)
{
  int win_sequence = 0;
  for (int i = 0; i < 5; ++i) {
    win_sequence = (win_sequence << 1) + Player;
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
  if(check_winner(PLAYER_0)) return true;
  if(check_winner(AI)) return true;

  //Search for blank spaces
  for(auto i = 0; i < GRID_SIZE; ++i)
    for(auto j = 0; j < GRID_SIZE; ++j)
      if(grid[i][j] == -1)
        return false;

  return true;
}
void print_grid(const int (&array)[GRID_SIZE][GRID_SIZE]) {

  std::string print = "";
  for(auto i = 0; i < 15; ++i){
    for(auto j = 0; j < 15; ++j) {
      print += std::to_string(array[i][j]) + "   ";
    }
    print += "\n";
  }
  std::cout << print << std::endl;
}

int max_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta);

int min_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta) {
  if(depth == 0 || game_over()) 
    return evaluate(state, AI);

  auto best_score = beta;
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
        state[i][j] = AI;
        auto temp_score = max_search(state, depth-1, alpha, best_score);
        if(temp_score < best_score)
          best_score = temp_score;
        
        if(best_score < alpha)
          state[i][j] = -1;
          return alpha;

        state[i][j] = -1;
      }
    }
  }
  return best_score;
}

int max_search(int (&state)[GRID_SIZE][GRID_SIZE], int depth, int alpha, int beta) {
  ++count;
  if(depth == 0 || game_over()) 
    return evaluate(state, AI);
  
  auto best_score = alpha;
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
        state[i][j] = PLAYER_0;
        auto temp_score = min_search(state, depth-1, best_score, beta);
        if(temp_score > best_score)
          best_score = temp_score;
        
        if(best_score > beta)
          state[i][j] = -1;
          return beta;

        state[i][j] = -1;
      }
    }
  }
  return best_score;
}

std::tuple<int,int> minimax(int (&state)[GRID_SIZE][GRID_SIZE],int depth) {
  int best_score = INT32_MAX;
  std::tuple<int,int> best_move;
  auto alpha = INT32_MIN;
  auto beta = INT32_MAX;
  for(auto i = 0; i < GRID_SIZE; ++i){
    for(auto j = 0; j < GRID_SIZE; ++j) {
      if(state[i][j] == -1) {
        state[i][j] = AI;
        auto temp_score = max_search(state, depth-1, alpha, beta);
        if(temp_score < best_score) {
          best_score = temp_score;
          best_move = std::tuple<int,int>(i, j);
        }
        state[i][j] = -1;
      }
    }
  }
  return best_move;
}

void populate_grid()
{
  for(auto i = 0; i < 15; ++i)
    for(auto j = 0; j < 15; ++j)
      grid[i][j] = -1;

  // for(auto i = 14, j=1; i > 10; --i)
  //   grid[i][j] = AI;

  // for(auto j = 14, i=1; j > 9; --j)
  //   grid[i][j] = AI;

    // grid[14][1] = 0;
  // for(auto i = 9, j=1; i > 5; --i, ++j)
    // grid[i][j] = PLAYER_0;
}


int main()
{
  populate_grid();
  std::cout << std::boolalpha << std::endl;

  auto t_start = std::chrono::high_resolution_clock::now();

  auto tuple = minimax(grid, 1);
  std::cout <<  "X = "<< std::get<0>(tuple) << std::endl
            <<  "Y = "<< std::get<1>(tuple) << std::endl;

  std::cout <<  "GRADE = " << evaluate(grid, AI) << std::endl;
  std::cout <<  "WIN = " << check_winner(AI) << std::endl;
  std::cout << count << std::endl;
  print_grid(grid);
  auto t_end = std::chrono::high_resolution_clock::now();


  std::cout << "grid: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";
 
}