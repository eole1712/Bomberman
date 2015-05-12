#ifndef __BUFFFACTORY_HPP__
# define __BUFFFACTORY_HPP__

# include "SmartFactory.hpp"
# include "IBuff.hpp"

namespace Bomberman
{

class BuffFactory : public SmartFactory<IBuff>
{
public:
  BuffFactory();
  ~BuffFactory();

private:
  BuffFactory(BuffFactory const& other);
  BuffFactory&	operator=(BuffFactory const& other);
};

}

#endif /* !__BUFFFACTORY_HPP__ */
