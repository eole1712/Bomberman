#ifndef __BUFFFACTORY_HPP__
# define __BUFFFACTORY_HPP__

# include "SmartFactory.hpp"
# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class Factory : public SmartFactory<IBuff>
  {
  public:
    Factory();
    ~Factory();
    static SmartFactory<IBuff>*	getInstance();
  private:
    Factory(Factory const& other);
    Factory&	operator=(Factory const& other);
  };
}
}

#endif /* !__BUFFFACTORY_HPP__ */
