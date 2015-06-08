#include "AMenuObject.hpp"

AMenuObject::AMenuObject(int x, int y, int width, int height, std::string const& texName)
  : _x(x), _y(y), _width(width), _height(height)
{
  _hidden = false;
  _texture.load(texName);
}

AMenuObject::~AMenuObject()
{
  ;
}

void	AMenuObject::setHidden(bool hidden)
{
  _hidden = hidden;
}

bool	AMenuObject::isHidden()
{
  return _hidden;
}

int	AMenuObject::getX()
{
  return _x;
}

int	AMenuObject::getY()
{
  return _y;
}
