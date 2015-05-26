#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "Game.hpp"
#include "Asset3d.hpp"

#include "RessourceStock.hpp"
#include "Map.hpp"
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffParalyzed.hpp"
#include "Player.hpp"
#include "Game.hpp"

using namespace Bomberman;

Game::Game()
  : _width(1024), _height(480), _camera(90.0, 1024, 480), _speed(70),
    _stock(std::vector<std::string> {"Adrien"}),
    _map("blibi", _width, _height, 1, Bomberman::Map::EASY, &_stock)
{
}

Game::Game(const unsigned int & width, const unsigned int & height)
  : _width(width), _height(height), _camera(90.0, width, height), _speed(70),
    _stock(std::vector<std::string> {"Adrien"}),
    _map("blibi", _width, _height, 1, Bomberman::Map::EASY, &_stock)
{
}

Game::~Game()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
    delete (*i);
}

bool				Game::initialize()
{
  std::vector<std::string>	vec;

  if (!_context.start(_width, _height, "My bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // vec.push_back("Adrien");
  // vec.push_back("Léon");
  // Bomberman::RessourceStockstock(vec);
  // -  Bomberman::Mapyooooo("blibi", 10, 10, 2, Bomberman::Map::EASY, stock);


  // We create a shader
  if (!_shader.load("srcs/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("srcs/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;
  attachObject(new Asset3d("srcs/assets/floor.obj"));
  attachObject(new Asset3d("srcs/assets/idst_block.obj"));
  attachObject(new Asset3d("srcs/assets/idst_block.obj"));
  attachObject(new Asset3d("srcs/assets/dst_block.obj"));
  attachObject(new Asset3d("srcs/assets/fire.obj"));
  attachObject(new Asset3d("scrs/assets/marvin.fbx"));
  _assets[PLAYER]->scale(glm::vec3(0.002));
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[PLAYER]->createSubAnim(0, "start", 0, 34);
  _assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  _assets[PLAYER]->createSubAnim(0, "end", 55, 100);
  _assets[PLAYER]->createSubAnim(0, "end2", 0, 1);
  attachObject(new Asset3d("srcs/assets/barrel.obj"));
  _assets[BOMB]->scale(glm::vec3(0.06));
  attachObject(new Asset3d("srcs</assets/sky.obj"));
  _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, -30, _height / 2));
  _camera.setRotation(_assets[PLAYER]->getPosition());
  _camera.setPosition(_assets[PLAYER]->getPosition() + glm::vec3(3.5, 3.5, 3));
  _camera.updateView();
  // We have the bind the shader before calling the setUniform method
  _shader.bind();
  return true;
}

void		Game::attachObject(Asset3d *obj)
{
  _assets.push_back(obj);
}

bool		Game::update()
{
  float		movefactor;
  glm::vec3	move;
  glm::vec3	newPos;
  static int	change = 0;

  movefactor = static_cast<float>(_clock.getElapsed()) * _speed;
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;

  if (_input.getKey(SDLK_UP) || _input.getKey(SDLK_DOWN))
    {
      if (change == 0)
	{
	  _assets[PLAYER]->setCurrentSubAnim("start", false);
	  _assets[PLAYER]->setCurrentSubAnim("run", true);
	}
      change = 1;
      move = (_input.getKey(SDLK_UP)) ? glm::vec3(0, 0, 0.06) : glm::vec3(0, 0, -0.06);
      move = glm::rotate(move, _assets[PLAYER]->getRotation().y,
			 glm::vec3(0, 1, 0)) * movefactor;
      newPos = _assets[PLAYER]->getPosition() + move;
      if (newPos.x < 1 || newPos.x > _width)
	newPos = glm::vec3(_assets[PLAYER]->getPosition().x, newPos.y, newPos.z);
      if (newPos.z < 1 || newPos.z > _height)
	newPos = glm::vec3(newPos.x, newPos.y, _assets[PLAYER]->getPosition().z);
      _assets[PLAYER]->setPosition(newPos);
      _camera.setRotation(newPos);
      _camera.updateView();
    }
  else if (change == 1)
    {
      change = 0;
      _assets[PLAYER]->setCurrentSubAnim("end", false);
      // _assets[PLAYER]->setCurrentSubAnim("end2", true);
    }
  if (_input.getKey(SDLK_LEFT))
    _assets[PLAYER]->rotate(glm::vec3(0, 1, 0), 3 * movefactor);
  else if (_input.getKey(SDLK_RIGHT))
    _assets[PLAYER]->rotate(glm::vec3(0, 1, 0), -3 * movefactor);
  _camera.setPosition(_assets[PLAYER]->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    _assets[PLAYER]->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.updateView();
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  return true;
}

void		Game::draw()
{
  unsigned int	i[2];

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _shader.setUniform("view", _camera.getView());
  _shader.setUniform("projection", _camera.getProjection());
  // We draw all objects
  i[0] = 0;
  while (i[0] < _width)
    {
      i[1] = 0;
      while (i[1] < _height)
	{
	  if (i[0] == 0 || i[1] == 0 || i[0] == _width || i[1] == _height)
	    {
	      _assets[WALL]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[WALL]->draw(_shader, _clock);
	    }
	  else if (1)
	    {
	      _assets[IDST_BLOCK]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[IDST_BLOCK]->draw(_shader, _clock);
	    }
	  else
	    {
	      _assets[FLOOR]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[FLOOR]->draw(_shader, _clock);
	    }
	  i[1]++;
	}
      i[0]++;
    }
  _assets[DST_BLOCK]->setPosition(glm::vec3(rand() % 12 * 2, 0, rand() % 12 * 2));
  _assets[DST_BLOCK]->draw(_shader, _clock);
  _assets[PLAYER]->draw(_shader, _clock);
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  _assets[SKYBOX]->scale(glm::vec3(-1));
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->scale(glm::vec3(1));
  _context.flush();
}
