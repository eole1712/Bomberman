#ifndef __SAFEQUEUEFINISHED_HPP__
# define __SAFEQUEUEFINISHED_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class SafeQueueFinished : public std::runtime_error
  {
  public:
    SafeQueueFinished() throw();
    virtual ~SafeQueueFinished() throw();
  };
}

#endif /* !__SAFEQUEUEFINISHED_HPP__ */
