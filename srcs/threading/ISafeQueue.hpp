#ifndef __ISAFEQUEUE_HPP__
# define __ISAFEQUEUE_HPP__

template <typename T>
class ISafeQueue
{
public:
  virtual ~ISafeQueue(void) {}

public:
  virtual void	push(T value) = 0;
  virtual T	pop(void) = 0;
  virtual bool	tryPop(T* value) = 0;
  virtual bool	isEmpty(void) = 0;
  virtual int	length(void) = 0;
  virtual bool	isFinished(void) const = 0;
  virtual void	setFinished(void) = 0;
};

#endif /* !__ISAFEQUEUE_HPP__ */
