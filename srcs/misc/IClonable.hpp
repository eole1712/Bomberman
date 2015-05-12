#ifndef __ICLONABLE_HPP__
# define __ICLONABLE_HPP__

class IClonable
{
public:
  ~IClonable() {}

public:
  virtual IClonable*	clone() const = 0;
};

#endif /* !__ICLONABLE_HPP__ */
