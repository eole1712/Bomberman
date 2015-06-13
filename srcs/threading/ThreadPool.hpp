#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "Thread.hpp"
# include "SafeQueue.hpp"

template <typename T, typename S>
class ThreadPool
{
public:
  ThreadPool(typename Thread<T, S>::ThreadFunc func, int nbThreads = 5)
    :_shouldRun(true), _execFunc(func)
  {
    typename std::vector<Thread<void*, void*> >::iterator	it;
    std::pair<void*, void* >*					pair;
    int								i;

    i = 0;
    while (i < nbThreads)
      {
	_threads.push_back(Thread<void*, void*>());
	i++;
      }
    it = _threads.begin();
    while (it < _threads.end())
      {
	pair = new std::pair<void*, void*>;
	pair->second = this;

	pair->first = &(*it);
	(*it).start(&run_thread, pair, false);
	it++;
      }
  }

  ~ThreadPool()
  {
    typename std::vector<Thread<void*, void*> >::iterator	it;

    stopRun();
    it = _threads.begin();
    while (it != _threads.end())
      {
	(*it).join();
	it++;
      }
  }

  static void*		run_thread(void* data)
  {
    std::pair<void*, void* >*	pair;
    ThreadPool<T, S>*		tp;
    Thread<void*, void*>*	t;

    pair = static_cast<std::pair<void*, void*>* >(data);
    tp = static_cast<ThreadPool<T, S>* >(pair->second);
    t = static_cast<Thread<void*, void*>* >(pair->first);
    tp->exec_thread(t);
    return NULL;
  }

  void		exec_thread(Thread<void*, void*>* thread)
  {
    T		data;

    while (_shouldRun)
      {
	if (_queue.tryPop(&data))
	  {
	    thread->noyield();
	    _execFunc(data);
	  }
	else
	  {
	    thread->yield();
	  }
      }
    pthread_exit(NULL);
  }

  int				used_threads()
  {
    typename std::vector<Thread<void*, void*> >::iterator	it;
    int								i;

    i = 0;
    it = _threads.begin();
    while (it < _threads.end())
      {
	if ((*it).getStatus() == Thread<void*, void*>::Status::RUNNING)
	  i++;
	it++;
      }
    return i;
  }

  void				stopRun()
  {
    _shouldRun = false;
  }

  bool				isEmpty()
  {
    return (_queue.isEmpty());
  }

  int				countTask()
  {
    return (_queue.length());
  }

  void				addTask(T task)
  {
    _queue.push(task);
  }

  bool				allDead()
  {
    typename std::vector<Thread<void*, void*> >::iterator	it;

    it = _threads.begin();
    while (it < _threads.end())
      {
	if ((*it).getStatus() == Thread<void*, void*>::Status::RUNNING)
	  return false;
	it++;
      }
    return true;
  }

private:
  ThreadPool<T, S>(const ThreadPool<T, S> & other);
  ThreadPool<T, S>&				operator=(const ThreadPool<T, S>& other);
  bool						_shouldRun;
  typename Thread<T, S>::ThreadFunc		_execFunc;
  std::vector<Thread<void*, void*> >		_threads;
  SafeQueue<T>					_queue;
};

#endif /* !THREADPOOL_H_ */
