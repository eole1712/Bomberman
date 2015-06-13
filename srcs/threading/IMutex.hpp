#ifndef __IMUTEX_HPP__
# define __IMUTEX_HPP__

class IMutex
{
public:
  virtual	~IMutex(void) {}
  virtual void	lock(void) = 0;
  virtual void	unlock(void) = 0;
  virtual bool	trylock(void) = 0;
};

#endif /* !__IMUTEX_HPP__ */
