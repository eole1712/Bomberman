#ifndef __INVALIDDIMENSIONS_HPP__
# define __INVALIDDIMENSIONS_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class InvalidDimensions : public std::runtime_error
  {
  public:
    InvalidDimensions(std::string const& err) throw();
    virtual ~InvalidDimensions() throw();
  };
}

#endif /* !__INVALIDDIMENSIONS_HPP__ */
