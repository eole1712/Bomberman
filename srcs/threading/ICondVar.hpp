#ifndef __ICONDVAR_HPP__
# define __ICONDVAR_HPP__

class ICondVar
{
public:
  virtual	~ICondVar() {}

public:
  virtual void	wait(void) = 0;
  virtual void	signal(void) = 0;
  virtual void	broadcast(void) = 0;
};

#endif /* !__ICONDVAR_HPP__ */
