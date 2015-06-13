#include "SafeQueueFinished.hpp"

namespace Exception
{
  SafeQueueFinished::SafeQueueFinished() throw():
    std::runtime_error("SafeQueue status is finished")
  {
  }

  SafeQueueFinished::~SafeQueueFinished() throw()
  {
  }
}
