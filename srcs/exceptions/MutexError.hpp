#ifndef __MUTEXERROR_HPP__
# define __MUTEXERROR_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class MutexError : public std::logic_error
  {
  public:
    MutexError(std::string const& err) throw();
    virtual ~MutexError() throw();
  };
}

#endif /* !__MUTEXERROR_HPP__ */
