#include "AMenuObject.hpp"
#include <iostream>

AMenuObject::AMenuObject(int x, int y, int width, int height, std::string const& texName)
  : _x(x), _y(y), _width(width), _height(height), _focusable(true), _fShowable(true), _dynamic(false)
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

void	AMenuObject::hideFocus()
{
  _fShowable = false;
}

bool	AMenuObject::isHidden() const
{
  return _hidden;
}

int	AMenuObject::getX() const
{
  return _x;
}

int	AMenuObject::getY() const
{
  return _y;
}

int	AMenuObject::getHeight() const
{
  return _height;
}

bool	AMenuObject::isFocusable() const
{
  return _focusable;
}

bool	AMenuObject::showFocus() const
{
  return _fShowable;
}

void	AMenuObject::unFocus()
{
  _focusable = false;
}

void	AMenuObject::setDynamic()
{
  _dynamic = true;
}

bool	AMenuObject::isDynamic() const
{
  return _dynamic;
}
