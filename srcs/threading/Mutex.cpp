#include <cerrno>
#include <cstring>
#include "Mutex.hpp"
#include "MutexError.hpp"
#include "ResourceUnavailable.hpp"
#include "CondVarError.hpp"

Mutex::Mutex()
{
  int	ret;

  ret = pthread_mutex_init(&_mutex, NULL);
  if (ret == EAGAIN || ret == ENOMEM)
    throw Exception::ResourceUnavailable("Resource temporarily unavailable");
  else if (ret == EINVAL)
    throw Exception::MutexError("Unknown internal error");
}

Mutex::~Mutex(void)
{
  int	ret;

  if ((ret = pthread_mutex_destroy(&_mutex)) == EBUSY)
    throw Exception::MutexError("Mutex is locked by a thread.");
  else if (ret == EINVAL)
    throw Exception::MutexError("Unknown internal error.");
}

void	Mutex::lock(void)
{
  int	ret;

  if ((ret = pthread_mutex_lock(&_mutex)) == EDEADLK)
    throw Exception::MutexError("Deadlock would occur.");
  else if (ret == EINVAL)
    throw Exception::MutexError("Unknown internal error.");
}

void	Mutex::unlock(void)
{
  int	ret;

  if ((ret = pthread_mutex_unlock(&_mutex)) == EINVAL)
    throw Exception::MutexError("Unknown internal error");
  else if (ret == EPERM)
    throw Exception::MutexError("The current thread does not hold a lock on mutex.");
}

bool	Mutex::trylock(void)
{
  int	ret;

  if ((ret = pthread_mutex_trylock(&_mutex)) == EBUSY)
    return (false);
  else if (ret != 0)
    throw Exception::MutexError("Unknown internal error");
  return (true);
}

void	Mutex::condVarWait(pthread_cond_t* cv)
{
  if (pthread_cond_wait(cv, &_mutex) != 0)
    throw Exception::CondVarError("Unknown internal error");
}
