#include "Text2d.hpp"
#include "MenuGrid.hpp"
#include <iostream>

MenuGrid::MenuGrid(std::string const& texName)
{
  if (texName != "")
    _focusTexture.load(texName);
  //  _focus = _elems.begin();
}

MenuGrid::~MenuGrid()
{
  ;
}

void	MenuGrid::moveLeft()
{
  _focus = _focus == _elems.begin() ? _elems.end() - 1 : _focus - 1;
}

void	 MenuGrid::moveRight()
{
  _focus = _focus + 1 == _elems.end() ? _elems.begin() : _focus + 1;
}

void	MenuGrid::drawAll(gdl::Clock &, gdl::BasicShader &shader, std::vector<Asset3d *> &, std::map<Bomberman::IObject::Type, Bomberman::mapAsset>)
{
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin(); it != _elems.end(); ++it)
    {
      if (!(*it).first->isHidden())
	(*it).first->draw(shader);
      if (_focus == it)
	drawFocus((*it).first->getX(), (*it).first->getY(), shader);
    }
}

void	MenuGrid::addObject(AMenuObject* obj, std::function<void()> func)
{
  _elems.push_back(std::pair<AMenuObject*, std::function<void()> >(obj, func));
  _focus = _elems.begin();
  func();
}

void	MenuGrid::actionOnFocus()
{
  (*_focus).second();
}

void	MenuGrid::drawFocus(int x, int y, gdl::BasicShader& shader)
{
  Text2d	cursor("S", x - 70, y, 50, 50, "../assets/textures/alpha2.tga");

  cursor.draw(shader);
}


}
