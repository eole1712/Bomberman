#ifndef BUFFTIMER_H_
# define BUFFTIMER_H_

# include "buffs/IBuff.hpp"
# include "../misc/Timer.hpp"

namespace Bomberman
{

class BuffTimer
  : public Timer
{
public:
  BuffTimer(IBuff *);
  BuffTimer(IBuff *, unsigned int time);
  virtual ~BuffTimer();

private:
  BuffTimer(const BuffTimer &);
  BuffTimer &operator=(const BuffTimer &);

public:
  IBuff const	*getBuff() const;

private:
  IBuff		*_buff;
};

}

#endif /* !BUFFTIMER_H_ */
