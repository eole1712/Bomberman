#ifndef __INVALIDNBPLAYERS_HPP__
# define __INVALIDNBPLAYERS_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class InvalidNbPlayers : public std::runtime_error
  {
  public:
    InvalidNbPlayers(std::string const& err) throw();
    virtual ~InvalidNbPlayers() throw();
  };
}

#endif /* !__INVALIDNBPLAYERS_HPP__ */
