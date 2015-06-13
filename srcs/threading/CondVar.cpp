#include <cerrno>
#include <cstring>
#include "CondVarError.hpp"
#include "ResourceUnavailable.hpp"
#include "CondVar.hpp"

CondVar::CondVar(Mutex& mutex) : _mutex(mutex)
{
  int	ret;

  if ((ret = pthread_cond_init(&_cv, NULL)) == EINVAL)
    throw Exception::CondVarError("Unknown internal error");
  else if (ret != 0)
    throw Exception::ResourceUnavailable("Resource temporarily unavailable");
}

CondVar::~CondVar()
{
  int	ret;

  if ((ret = pthread_cond_destroy(&_cv)) == EBUSY)
    throw Exception::CondVarError("Conditional variable locked by another thread");
  else if (ret == EINVAL)
    throw Exception::CondVarError("Unknown internal error");
}

void	CondVar::wait(void)
{
  _mutex.condVarWait(&_cv);
}

void	CondVar::signal(void)
{
  if (pthread_cond_signal(&_cv) != 0)
    throw Exception::CondVarError("Unknown internal error");
}

void	CondVar::broadcast(void)
{
  int	ret;

  if ((ret = pthread_cond_broadcast(&_cv)) != 0)
    throw Exception::CondVarError("Unknown internal error");
}
