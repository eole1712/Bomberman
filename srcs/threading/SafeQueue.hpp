#ifndef __SAFEQUEUE_HPP__
# define __SAFEQUEUE_HPP__

# include <queue>
# include "ISafeQueue.hpp"
# include "ScopedLock.hpp"
# include "Mutex.hpp"
# include "CondVar.hpp"
# include "SafeQueueFinished.hpp"

template <typename T>
class SafeQueue : public ISafeQueue<T>
{
public:
  SafeQueue() : _condvar(_mutex), _finished(false)
  {
  }

  virtual ~SafeQueue(void)
  {
  }

public:
  virtual void	push(T data)
  {
    ScopedLock	lock(_mutex);

    _queue.push(data);
    _condvar.signal();
  }

  virtual T	pop(void)
  {
    ScopedLock	lock(_mutex);
    T		data;

    while (_queue.empty())
      {
	_condvar.wait();
	if (_finished)
	  throw Exception::SafeQueueFinished();
      }
    data = _queue.front();
    _queue.pop();
    return (data);
  }

  virtual bool	tryPop(T* data)
  {
    ScopedLock	lock(_mutex);

    if (_queue.empty())
      return (false);
    if (data != NULL)
      *data = _queue.front();
    _queue.pop();
    return (true);
  }

  virtual bool	isEmpty(void)
  {
    ScopedLock	lock(_mutex);

    return _queue.empty();
  }

  virtual int	length(void)
  {
    ScopedLock	lock(_mutex);

    return _queue.size();
  }

  virtual bool	isFinished(void) const
  {
    return (_finished);
  }

  virtual void	setFinished(void)
  {
    _finished = true;
    _condvar.broadcast();
  }

private:
  SafeQueue(const SafeQueue& other);
  SafeQueue&		operator=(const SafeQueue& other);

  std::queue<T>	_queue;
  Mutex		_mutex;
  CondVar	_condvar;
  bool		_finished;
};

#endif /* !__SAFEQUEUE_HPP__ */
