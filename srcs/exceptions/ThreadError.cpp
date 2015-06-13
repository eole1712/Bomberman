#include "ThreadError.hpp"

namespace Exception
{
  ThreadError::ThreadError(std::string const& err) throw():
    std::logic_error(err)
  {
  }

  ThreadError::~ThreadError() throw()
  {
  }
}
