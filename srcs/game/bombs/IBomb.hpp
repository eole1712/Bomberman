#ifndef IBOMB_H_
# define IBOMB_H_

# include "IObject.hpp"

namespace Bomberman
{

class IBomb
{
public:
  enum Type
    {
      CLASSIC = 0
    };

public:
  virtual ~IBomb() {}

public:
  virtual int		getDuration() const = 0;
  virtual Type		getBombType() const = 0;

public:
  static const int	nbBomb;
};

}

#endif /* !IBOMB_H_ */
