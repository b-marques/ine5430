#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#define GRID_SIZE_M_1 14
#define GRID_SIZE 15
#include "gomoku_player.h"
#include <tuple>

enum GameState {
	NEW_GAME = 0, IN_GAME, END_GAME,
};

enum PlayerTurn {
	P1 = 0, P2 = 1,
};

class GomokuCore {
public:
	static GomokuCore* instance();
	~GomokuCore();
	void restart();
	void change_turn();
	bool compute_play(int x, int y);
	bool have_winner(int player);
	bool game_over();
	PlayerTurn player_turn();
	GameState game_state();
	std::tuple<int, int> minimax(int depth);
	void game_state(GameState state);
	int conta_iteracoes();

private:
	GomokuCore();
	static GomokuCore* _instance;
	void update_grid(int x, int y);
	void populate_grid();
	int evaluate_incremental(int x, int y, int (&grid)[GRID_SIZE][GRID_SIZE],
			int turn);
	void treats_sequence_incremental(int& add_to_grade, int* sequence,
			int seq_size, int play_position, int turn);
	void evaluate_sequence(int& n_unities_open, int& n_doubles_open,
			int& n_triples_open, int& n_quadruples_open, int& n_quintuples,
			int sequence, int n_opens);
	std::tuple<int, int> minimax_updown(int depth);
	std::tuple<int, int> minimax_downup(int depth);
	int max_search_updown(int (&state)[GRID_SIZE][GRID_SIZE], int depth,
			int alpha, int beta, int last_grade, int added_to_grade);
	int max_search_downup(int (&state)[GRID_SIZE][GRID_SIZE], int depth,
			int alpha, int beta, int last_grade, int added_to_grade);
	int min_search_updown(int (&state)[GRID_SIZE][GRID_SIZE], int depth,
			int alpha, int beta, int last_grade, int added_to_grade);
	int min_search_downup(int (&state)[GRID_SIZE][GRID_SIZE], int depth,
			int alpha, int beta, int last_grade, int added_to_grade);
	int evaluate(int (&grid)[GRID_SIZE][GRID_SIZE], int turn, int depth);
	void treats_sequence(int (&grid)[GRID_SIZE][GRID_SIZE], const int i,
			const int j, int turn, int& sequence, int& n_opens,
			int& last_position, int& n_unities_open, int& n_doubles_open,
			int& n_triples_open, int& n_quadruples_open, int& n_quintuples,
			bool reached_grid_limit);

	int _grid[GRID_SIZE][GRID_SIZE];
	PlayerTurn _player_turn;
	GameState _game_state;
	GomokuPlayer _player[2];
	int _conta_iteracoes;
	int _up_board_plays;
	int _down_board_plays;
};

#endif // GOMOKU_CORE_H
