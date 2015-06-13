#ifndef __SCOPEDLOCK_HPP__
# define __SCOPEDLOCK_HPP__

# include "IMutex.hpp"

class ScopedLock
{
public:
  ScopedLock(IMutex& mutex);
  virtual ~ScopedLock();

private:
  IMutex&	_mutex;
};

#endif /* !__SCOPEDLOCK_HPP__ */
