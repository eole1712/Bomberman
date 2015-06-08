#include <math.h>
#include "Score.hpp"

namespace Bomberman
{

const int	Score::dftTime = 10;

Score::Score()
  : _score(0), _timer(NULL), _killStreak(0)
{}

Score::~Score()
{}

unsigned int	Score::getScore() const
{
  return (this->_score);
}

void		Score::inc()
{
  if (this->_timer == NULL || this->_timer->isFinished())
    {
      if (this->_timer != NULL)
	{
	  delete this->_timer;
	  this->_killStreak = 0;
	}
      this->_timer = new Timer(Score::dftTime * 1000000);
    }
  else
    {
      delete this->_timer;
      this->_timer = new Timer((Score::dftTime + this->_killStreak * 2) * 1000000);
    }
  this->_timer->start();
  this->_score += 100 * pow(2, this->_killStreak);
  ++this->_killStreak;
}

}