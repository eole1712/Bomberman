#ifndef THREADERROR_H_
# define THREADERROR_H_

# include <string>
# include <stdexcept>

namespace Exception
{
  class ThreadError : public std::logic_error
  {
  public:
    ThreadError(std::string const& err) throw();
    virtual ~ThreadError() throw();
  };
}

#endif /* !THREADERROR_H_ */
