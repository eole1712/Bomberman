#ifndef __RESOURCEUNAVAILABLE_HPP__
# define __RESOURCEUNAVAILABLE_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class ResourceUnavailable : public std::runtime_error
  {
  public:
    ResourceUnavailable(std::string const& err) throw();
    virtual ~ResourceUnavailable() throw();
  };
}

#endif /* !__RESOURCEUNAVAILABLE_HPP__ */
