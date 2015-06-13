#include "MutexError.hpp"

namespace Exception
{
  MutexError::MutexError(std::string const& err) throw():
    std::logic_error(err)
  {
  }

  MutexError::~MutexError() throw()
  {
  }
}
