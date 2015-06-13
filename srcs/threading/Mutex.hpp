#ifndef __MUTEX_HPP__
# define __MUTEX_HPP__

# include <pthread.h>
# include "IMutex.hpp"
# include "CondVar.hpp"

class Mutex : public IMutex
{
public:
  Mutex();
  virtual	 ~Mutex(void);

  virtual void	lock(void);
  virtual void	unlock(void);
  virtual bool	trylock(void);
  void		condVarWait(pthread_cond_t* cv);

private:
  pthread_mutex_t	_mutex;
};

#endif /* !__MUTEX_HPP__ */
