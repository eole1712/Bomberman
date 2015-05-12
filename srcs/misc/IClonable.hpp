#ifndef __ICLONABLE_HPP__
# define __ICLONABLE_HPP__

# include <string>

template <typename Clone>
class IClonable
{
public:
  ~IClonable() {}

public:
  virtual Clone*	clone() const = 0;
  virtual std::string	getClassName() const = 0;
};

#endif /* !__ICLONABLE_HPP__ */
