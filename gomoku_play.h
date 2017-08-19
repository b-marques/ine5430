#ifndef GOMOKU_PLAY_H
#define GOMOKU_PLAY_H

#include <functional>

class GomokuPlay
{
public:
  GomokuPlay(int x, int y);
  ~GomokuPlay();
  int x() const;
  int y() const;
  bool operator == (const GomokuPlay& aux) const;

private:
	int _x, _y;
};

// Defining hash to a play, thus we can use unordered_set with average find complexity O(1).
namespace std
{
  template <> struct hash<GomokuPlay>
  {
    size_t operator()(const GomokuPlay& aux) const noexcept
    {
      return (
        (51 +std::hash<int>()(aux.x())) * 51
        + std::hash<int>()(aux.y())
      );
    }
  };
}
#endif // GOMOKU_PLAY_H
