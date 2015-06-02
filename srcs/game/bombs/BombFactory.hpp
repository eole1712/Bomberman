#ifndef BOMBFACTORY_H_
# define BOMBFACTORY_H_

# include "SmartFactory.hpp"
# include "IBomb.hpp"

namespace Bomberman
{
namespace Bomb
{
  class Factory : public SmartFactory<IBomb>
  {
  public:
    Factory();
    ~Factory();
    static SmartFactory<IBomb>*	getInstance();
  private:
    Factory(Factory const& other);
    Factory&	operator=(Factory const& other);
  };
}
}


#endif /* !BOMBFACTORY_H_ */
