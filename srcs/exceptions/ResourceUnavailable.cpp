#include "ResourceUnavailable.hpp"

namespace Exception
{
  ResourceUnavailable::ResourceUnavailable(std::string const& err) throw():
    std::runtime_error(err)
  {
  }

  ResourceUnavailable::~ResourceUnavailable() throw()
  {
  }
}
