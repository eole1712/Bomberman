#include <algorithm>
#include <iostream>
#include "View2d.hpp"
#include "Text2d.hpp"
#include "MenuGrid.hpp"
#include "SDL_events.h"

MenuGrid::MenuGrid(std::string const& texName)
  : _camera(90.0, 1000, 1000), _prev(0)
{
  if (texName != "")
    _focusTexture.load(texName);
  _elems.clear();
  _ftab[0] = [this] () {
    if (_prev != SDLK_UP)
      {
	moveLeft();
	_prev = SDLK_UP;
      }
  };
  _ftab[1] = [this] () {
    if (_prev != SDLK_UP)
      {
	moveLeft();
	_prev = SDLK_UP;
      }
  };
  _ftab[2] = [this] () {
    if (_prev != SDLK_DOWN)
      {
	moveRight();
	_prev = SDLK_DOWN;
      }
  };
  _ftab[3] = std::bind(&MenuGrid::actionOnFocus, this);
  _ftab[4] = [this] () {
    if ((*_focus).first->isDynamic())
      {
	(*_fnFocus).first();
      }
    _prev = SDLK_LEFT;
  };
  _ftab[5] = [this] () {
    if ((*_focus).first->isDynamic())
      {
	(*_fnFocus).second();
      }
    _prev = SDLK_RIGHT;
  };
  _prev = SDLK_RETURN;
}

MenuGrid::~MenuGrid()
{
  std::for_each(_elems.begin(), _elems.end(), [] (std::pair<AMenuObject*, std::function<void()> >& elem) {
      delete elem.first;
    });
}

void			MenuGrid::moveLeft()
{
  static unsigned int	nbTries = 0;

  _focus = _focus == _elems.begin() ? _elems.end() - 1 : _focus - 1;
  _fnFocus = _fnFocus == _funcs.begin() ? _funcs.end() - 1 : _fnFocus - 1;
  if (!(*_focus).first->isFocusable() && nbTries++ <= _elems.size())
    moveLeft();
  if (nbTries > _elems.size())
    _focus = _elems.end();
  nbTries = 0;
}

void			 MenuGrid::moveRight()
{
  static unsigned int	nbTries = 0;

  _focus = _focus + 1 == _elems.end() ? _elems.begin() : _focus + 1;
  _fnFocus = _fnFocus + 1 == _funcs.end() ? _funcs.begin() : _fnFocus + 1;
  if (!(*_focus).first->isFocusable() && nbTries <= _elems.size())
    {
      moveRight();
    }
  if (nbTries > _elems.size())
    _focus = _elems.end();
   nbTries = 0;
}

void			MenuGrid::drawAll(gdl::Clock &, gdl::BasicShader &shader,
					  std::vector<Asset3d *> &,
					  std::map<Bomberman::IObject::Type, Bomberman::mapAsset>&)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);

  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 1800.0f, 900.0f, 0.0f, -1.0f, 1.0f));
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin(); it != _elems.end(); ++it)
    {
      if (!(*it).first->isHidden())
	(*it).first->draw(shader);
      if (_focus == it && (*it).first->showFocus())
	drawFocus((*it).first->getX(), (*it).first->getY(), (*it).first->getHeight(), shader);
    }
  glEnable(GL_DEPTH_TEST);
}

void	MenuGrid::drawNoBack(gdl::BasicShader &shader)
{
  glDisable(GL_DEPTH_TEST);
  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 1800.0f, 900.0f, 0.0f, -1.0f, 1.0f));
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin(); it != _elems.end(); ++it)
    {
      if (!(*it).first->isHidden() && (*it).first->showFocus())
	{
	  (*it).first->draw(shader);
	}
      if (_focus == it)
	drawFocus((*it).first->getX(), (*it).first->getY(), (*it).first->getHeight(), shader);
    }
  glEnable(GL_DEPTH_TEST);
}

void	MenuGrid::addObject(AMenuObject* obj, std::function<void()> func)
{
  std::vector<std::pair< std::function<void()>, std::function<void()> > >::iterator it2;

  _elems.push_back(std::pair<AMenuObject*, std::function<void()> >(obj, func));
  _funcs.push_back(std::pair<std::function<void()>, std::function<void()> >([] () {}, [] () {}));
  it2 = _funcs.begin();
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin();
       it != _elems.end();
       ++it)
    {
      if ((*it).first->isFocusable())
	{
	  _focus = it;
	  _fnFocus = it2;
	  break;
	}
      ++it2;
    }
}


void	MenuGrid::addDynObject(AMenuObject* obj, std::function<void()> enter, std::function<void()> left, std::function<void()> right)
{
  std::vector<std::pair< std::function<void()>, std::function<void()> > >::iterator it2;

  _elems.push_back(std::pair<AMenuObject*, std::function<void()> >(obj, enter));
  _funcs.push_back(std::pair<std::function<void()>, std::function<void()> >(left, right));
  it2 = _funcs.begin();
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin();
       it != _elems.end();
       ++it)
    {
      if ((*it).first->isFocusable())
	{
	  _focus = it;
	  _fnFocus = it2;
	  break;
	}
      ++it2;
    }
}

void	MenuGrid::actionOnFocus()
{
  (*_focus).second();
  _prev = SDLK_RETURN;
}

void		MenuGrid::drawFocus(int x, int y, int height, gdl::BasicShader& shader)
{
  View2d	cursor(x - (height + 10), y, height, height, "resources/assets/textures/bombcursor.tga");

  cursor.draw(shader);
}

bool		MenuGrid::update(gdl::Clock &, gdl::Input & in)
{
  static int	idTab[] = {
    SDLK_UP, SDLK_TAB, SDLK_DOWN,
    SDLK_RETURN, SDLK_LEFT, SDLK_RIGHT
  };

  for (int i = 0; i < 6; ++i)
    {
      try {
	if (in.getKey(idTab[i]) && _prev != idTab[i])
	  _ftab[i]();
      }
      catch (std::bad_function_call e)
	{
	  std::cout << "Error in I/O" << e.what() << std::endl;
	}
    }
  if (!in.getKey(_prev))
    _prev = 0;
  std::for_each(_elems.begin(), _elems.end(), [&in, this] (std::pair<AMenuObject*, std::function<void()> >& button) {
      if (button.first == (*_focus).first)
	button.first->update(in);
    });
  _camera.updateView();
  return true;
}
