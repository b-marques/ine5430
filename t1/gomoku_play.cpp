#include "gomoku_play.h"

GomokuPlay::GomokuPlay(int x, int y) :
		_x(x), _y(y) {
}

GomokuPlay::~GomokuPlay() {
}

int GomokuPlay::x() const {
	return _x;
}

int GomokuPlay::y() const {
	return _y;
}

bool GomokuPlay::operator ==(const GomokuPlay& aux) const {
	return _x == aux._x && _y == aux._y;
}

