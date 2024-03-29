#ifndef SCORE_H_
# define SCORE_H_

# include "Timer.hpp"

namespace Bomberman
{

class RessourceStock;

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

  unsigned int	getValue() const;
  void		inc(RessourceStock*);
};

}

#endif /* !SCORE_H_ */
