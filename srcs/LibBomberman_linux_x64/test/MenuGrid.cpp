#include "Text2d.hpp"
#include "MenuGrid.hpp"
#include "SDL_events.h"
#include <iostream>

MenuGrid::MenuGrid(std::string const& texName)
  : _camera(90.0, 1000, 1000)
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

void	MenuGrid::drawAll(gdl::Clock &, gdl::BasicShader &shader, std::vector<Asset3d *> &, std::map<Bomberman::IObject::Type, Bomberman::mapAsset>&)
{
  //glViewport(900, 0, 900, 900);
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
  _focus = _elems.begin();
  //func();
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
  static int prev = 0;

  if (in.getKey(SDLK_ESCAPE) || in.getInput(SDL_QUIT))
    return false;
  if ((in.getKey(SDLK_UP) || in.getKey(SDLK_TAB)) && prev != SDLK_UP)
    {
      moveLeft();
      prev = SDLK_UP;
    }
  if (in.getKey(SDLK_DOWN) && prev != SDLK_DOWN)
    {
      moveRight();
      prev = SDLK_DOWN;
    }
  if (in.getKey(SDLK_RETURN))
    actionOnFocus();
  if (!in.getKey(prev))
    prev = 0;
  _camera.updateView();
  return true;
}
