#ifndef EMPTY_H_
# define EMPTY_H_

# include "IObject.hpp"

namespace Bomberman
{

class Empty
  : public IObject
{
public:
  Empty();
  virtual ~Empty();

private:
  Empty(const Empty &);
  Empty &operator=(const Empty &);

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};
}

#endif /* !EMPTY_H_ */
