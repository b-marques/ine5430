#ifndef GOMOKU_PLAYER_H
#define GOMOKU_PLAYER_H

#include <unordered_set>
#include "gomoku_play.h"

enum PlayerType {
	HUMAN = 0, COMPUTER = 1,
};

class GomokuPlayer {
public:
	GomokuPlayer();
	~GomokuPlayer();
	void play(int x, int y);
	bool already_played(int x, int y);
	std::unordered_set<GomokuPlay> plays();
	void clear_plays();
private:
	PlayerType _player_type;
	std::unordered_set<GomokuPlay> _plays;
};

#endif //GOMOKU_PLAYER_H
