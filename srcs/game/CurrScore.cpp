#include <math.h>
#include "CurrScore.hpp"

namespace Bomberman
{

const int	CurrScore::dftTime = 10;

CurrScore::CurrScore()
  : _score(0), _timer(NULL), _killStreak(0)
{}

CurrScore::~CurrScore()
{}

unsigned int	CurrScore::getScore() const
{
  return (this->_score);
}

void		CurrScore::inc()
{
  if (this->_timer == NULL || this->_timer->isFinished())
    {
      if (this->_timer != NULL)
	{
	  delete this->_timer;
	  this->_killStreak = 0;
	}
      this->_timer = new Timer(CurrScore::dftTime * 1000000);
    }
  else
    {
      delete this->_timer;
      this->_timer = new Timer((CurrScore::dftTime + this->_killStreak * 2) * 1000000);
    }
  this->_timer->start();
  this->_score += 100 * pow(2, this->_killStreak);
  ++this->_killStreak;
}

}
