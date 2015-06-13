
#ifndef THREAD_H_
# define THREAD_H_

# include <pthread.h>
# include <iostream>
# include <utility>
# include <cstring>
# include "ThreadError.hpp"

template <typename T, typename S>
class Thread
{
public:
  typedef	S	(*ThreadFunc)(T data);
  enum	Status
    {
      WAITING,
      RUNNING,
      DEAD
    };

public:
  Thread()
    :_status(WAITING)
  {

  }

  ~Thread() {}

public:
  Status getStatus() const
  {
    return _status;
  }

  S getRetValue() const
  {
    return _retValue;
  }

  void		start(ThreadFunc func, T data, bool shouldJoin = true)
  {
    std::pair<ThreadFunc, T>*	pairdata;
    void*			tmpRetValue;
    int				ret;

    if (_status == WAITING || _status == DEAD)
      {
	pairdata = new std::pair<ThreadFunc, T>;
	pairdata->first = func;
	pairdata->second = data;
	if ((ret = pthread_create(&_thread, NULL, &Thread::_runFunc, pairdata)) != 0)
	  throw Exception::ThreadError(strerror(ret));
	_status = RUNNING;
	if (shouldJoin)
	  {
	    if ((ret = pthread_join(_thread, &tmpRetValue)) != 0)
	      throw Exception::ThreadError(strerror(ret));
	    _retValue = *(static_cast<S*>(tmpRetValue));
	  }
      }
    else
      {
	throw Exception::ThreadError("Thread is Already used");
      }
  }

  void		join()
  {
    int		ret;
    void*	tmpRetValue;

 if ((ret = pthread_join(_thread, &tmpRetValue)) != 0)
      throw Exception::ThreadError(strerror(ret));
    _retValue = *(static_cast<S*>(tmpRetValue));
  }

  void		yield()
  {
    pthread_yield();
    _status = DEAD;
  }

  void		noyield()
  {
    _status = RUNNING;
  }

private:
  static void*	_runFunc(void* data)
  {
    std::pair<ThreadFunc, T>*	tmp;
    S	 			retval;

    tmp = static_cast<std::pair<ThreadFunc, T>* >(data);
    retval = (tmp->first)(tmp->second);
    delete tmp;
    pthread_exit(static_cast<void*>(&retval));
  }

private:
  Status	_status;
  S		_retValue;
  pthread_t	_thread;
};

#endif /* !THREAD_H_ */
