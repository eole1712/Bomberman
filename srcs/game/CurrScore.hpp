#ifndef CURRSCORE_H_
# define CURRSCORE_H_

#include "Timer.hpp"

namespace Bomberman
{

class	CurrScore
{
private:
  unsigned int	_score;
  Timer*	_timer;
  unsigned int	_killStreak;

public:
  CurrScore();
  ~CurrScore();

public:
  static const int	dftTime;

  unsigned int	getScore() const;
  void		inc();
};

}

#endif /* !CURRSCORE_H_ */
