#include "AMenuObject.hpp"
#include <iostream>

AMenuObject::AMenuObject(int x, int y, int width, int height, std::string const& texName)
  : _x(x), _y(y), _width(width), _height(height), _focusable(true)
{
  _hidden = false;
  if (!_texture.load(texName))
    std::cerr << "failed to build : " << texName << std::endl;;

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

int	AMenuObject::getHeight()
{
  return _height;
}

bool	AMenuObject::isFocusable()
{
  return _focusable;
}

void	AMenuObject::unFocus()
{
  _focusable = false;
}
