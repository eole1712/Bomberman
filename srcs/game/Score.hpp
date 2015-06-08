#ifndef SCORE_H_
# define SCORE_H_

#include "Timer.hpp"

namespace Bomberman
{

class	Score
{
private:
  unsigned int	_score;
  Timer*	_timer;
  unsigned int	_killStreak;

public:
  Score();
  ~Score();

public:
  static const int	dftTime;

  unsigned int	getScore() const;
  void		inc();
};

}

#endif /* !SCORE_H_ */
