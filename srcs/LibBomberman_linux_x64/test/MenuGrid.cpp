#include <algorithm>
#include <iostream>
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
}

MenuGrid::~MenuGrid()
{
  ;
}

void	MenuGrid::moveLeft()
{
  static unsigned int	nbTries = 0;

  _focus = _focus == _elems.begin() ? _elems.end() - 1 : _focus - 1;
  if (!(*_focus).first->isFocusable() && nbTries++ <= _elems.size())
    moveLeft();
  if (nbTries > _elems.size())
    _focus = _elems.end();
  nbTries = 0;
  std::cout << nbTries << std::endl;
}

void	 MenuGrid::moveRight()
{
  static unsigned int	nbTries = 0;

  _focus = _focus + 1 == _elems.end() ? _elems.begin() : _focus + 1;
  if (!(*_focus).first->isFocusable() && nbTries <= _elems.size())
    {
      moveRight();
    }
  if (nbTries > _elems.size())
    _focus = _elems.end();
   nbTries = 0;
  std::cout << nbTries << std::endl;
}

void	MenuGrid::drawAll(gdl::Clock &, gdl::BasicShader &shader, std::vector<Asset3d *> &, std::map<Bomberman::IObject::Type, Bomberman::mapAsset>&)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  shader.setUniform("view", _camera.getView());
  shader.setUniform("projection", _camera.getProjection());
  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, 1.0f));
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin(); it != _elems.end(); ++it)
    {
      if (!(*it).first->isHidden())
	{
	  (*it).first->draw(shader);
	}
      if (_focus == it)
	drawFocus((*it).first->getX(), (*it).first->getY(), shader);
    }
}

void	MenuGrid::addObject(AMenuObject* obj, std::function<void()> func)
{
  _elems.push_back(std::pair<AMenuObject*, std::function<void()> >(obj, func));
  for (std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator it = _elems.begin(); it != _elems.end(); ++it)
    {
      if ((*it).first->isFocusable())
	{
	  _focus = it;
	  break;
	}
    }
}

void	MenuGrid::actionOnFocus()
{
  (*_focus).second();
}

void	MenuGrid::drawFocus(int x, int y, gdl::BasicShader& shader)
{
  Text2d	cursor("S", x - 70, y, 50, 50, "resources/assets/textures/alpha3Blue.tga");

  cursor.draw(shader);
}

bool	MenuGrid::update(gdl::Clock &, gdl::Input & in)
{
  static int idTab[] = {
    SDLK_UP, SDLK_TAB, SDLK_DOWN, SDLK_RETURN
  };
  if (in.getKey(SDLK_ESCAPE) || in.getInput(SDL_QUIT))
    return false;
  try {
    for (int i = 0; i < 5; ++i)
      {
	if (in.getKey(idTab[i]) && _prev != idTab[i])
	  _ftab[i]();
      }
  }
  catch (std::bad_function_call e)
    {
      std::cout << "Error in I/O" << e.what() << std::endl;
      exit(-1);
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
