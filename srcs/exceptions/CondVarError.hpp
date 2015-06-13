#ifndef __CONDVARERROR_HPP__
# define __CONDVARERROR_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class CondVarError : public std::logic_error
  {
  public:
    CondVarError(std::string const& err) throw();
    virtual ~CondVarError() throw();
  };
}

#endif /* !__CONDVARERROR_HPP__ */
