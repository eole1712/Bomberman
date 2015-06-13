#ifndef __CONDVAR_HPP__
# define __CONDVAR_HPP__

# include <pthread.h>
# include "ICondVar.hpp"

# include "Mutex.hpp"

class Mutex;

class CondVar : public ICondVar
{
public:
  CondVar(Mutex& mutex);
  virtual	~CondVar();

public:
  virtual void	wait(void);
  virtual void	signal(void);
  virtual void	broadcast(void);

private:
  pthread_cond_t	_cv;
  Mutex&		_mutex;
};

#endif /* !__CONDVAR_HPP__ */
