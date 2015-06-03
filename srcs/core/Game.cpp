#include <vector>
#include <string>
#include <algorithm>
#include <map>
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

namespace Bomberman
{

Game::Game()
  : _width(20), _height(20), _camera(90.0, 1000, 1000), _speed(70),
    _stock(std::vector<std::string> {"Adrien", "Jean", "grigri", "bra", "bro"}),
    _map("blibi", _width, _height, _stock.getNbPlayer(), Map::EASY, &_stock)
{
  Player	*player;

  for (unsigned int i = 0; i < _stock.getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(_stock.getPlayer(i));
      player->initGame(&_map);
    }
}

Game::Game(const unsigned int & width, const unsigned int & height)
  : _width(width), _height(height), _camera(90.0, 1000, 1000), _speed(70),
    _stock(std::vector<std::string> {"Adrien", "Jean", "grigri", "bra", "bro"}),
    _map("blibi", _width, _height, _stock.getNbPlayer(), Map::EASY, &_stock)
{

  Player	*player;

  for (unsigned int i = 0; i < _stock.getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(_stock.getPlayer(i));
      player->initGame(&_map);
    }
}

Game::~Game()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
    delete (*i);
}

bool				Game::initialize()
{
  std::vector<std::string>	vec;
  Player			*player = dynamic_cast<Player *>(_stock.getPlayer(0));

  if (!_context.start(_camera._width, _camera._height, "My bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

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
  attachObject(new Asset3d("srcs/assets/marvin.fbx"));
  _assets[PLAYER]->scale(glm::vec3(0.002));
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[PLAYER]->createSubAnim(0, "start", 10, 28);
  _assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  _assets[PLAYER]->createSubAnim(0, "end", 55, 130);
  _assets[PLAYER]->createSubAnim(0, "end2", 0, 1);
  attachObject(new Asset3d("srcs/assets/barrel.obj"));
  _assets[BOMB]->scale(glm::vec3(0.06));
  _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
  attachObject(new Asset3d("srcs/assets/sky.obj"));
  _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, 0, _height / 2));
  // We have the bind the shader before calling the setUniform method

  _camera.setPosition(player->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition());
  _ObjectToAsset[IObject::BOMB] = BOMB;
  _ObjectToAsset[IObject::PLAYER] = PLAYER;
  _ObjectToAsset[IObject::BONUS] = FIRE;
  _ObjectToAsset[IObject::WALL] = IDST_BLOCK;
  _ObjectToAsset[IObject::DESTROYABLEWALL] = DST_BLOCK;
  _ObjectToAsset[IObject::SPAWN] = FLOOR;
  _ObjectToAsset[IObject::EMPTY] = FLOOR;
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
  static int	change = 0;
  Player	*player = dynamic_cast<Player *>(_stock.getPlayer(1));
  Player	*ai = dynamic_cast<Player *>(_stock.getPlayer(0));

  movefactor = static_cast<float>(_clock.getElapsed()) * _speed;
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;

  static bool	space = false;
  if (_input.getKey(SDLK_SPACE))
    {
      if (space)
	{
	  player->putBomb();
	}
      space = !space;
    }
  if (_input.getKey(SDLK_UP) || _input.getKey(SDLK_DOWN))
    {
      if (change == 0)
	{
	  _assets[PLAYER]->setCurrentSubAnim("start", false);
	  _assets[PLAYER]->setCurrentSubAnim("run", true);
	}
      change = 1;

      move = (_input.getKey(SDLK_UP)) ? glm::vec3(0, 0, 0.06) : glm::vec3(0, 0, -0.06);
      move = glm::rotate(move, player->getRotation().y, glm::vec3(0, 1, 0)) * movefactor;
      player->move(move);
      _camera.setRotation(player->getPosition());
      _camera.updateView();
    }
  else if (change == 1)
    {
      change = 0;
      _assets[PLAYER]->setCurrentSubAnim("end", false);
      // _assets[PLAYER]->setCurrentSubAnim("end2", true);
    }
  if (_input.getKey(SDLK_LEFT))
    player->Player::rotate(glm::vec3(0, 1, 0), 3 * movefactor);
  else if (_input.getKey(SDLK_RIGHT))
    player->Player::rotate(glm::vec3(0, 1, 0), -3 * movefactor);
  _map.checkBombsOnMap();

  // ia
  _camera.setRotation(ai->getPosition());
  _camera.setPosition(ai->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    ai->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  //  ai->move(glm::vec3(5, 5, 5) * movefactor);
  //ai->rotate(glm::vec3(0, 1, 0), 3 * movefactor);
  // end ia

  _camera.updateView();
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  return true;
}

void		Game::draw()
{
  int		i[2];
  unsigned int	y;
  Player	*player;

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _shader.setUniform("view", _camera.getView());
  _shader.setUniform("projection", _camera.getProjection());
  _shader.setUniform("color", glm::vec4(1.0));
  // We draw all objects
  i[0] = -1;
  while (i[0] <= _width)
    {
      i[1] = -1;
      while (i[1] <= _height)
	{
	  if (i[0] == -1 || i[1] == -1 || i[0] == _width || i[1] == _height)
	    {
	      _assets[WALL]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[WALL]->draw(_shader, _clock);
	    }
	  else
	    {
	      _assets[_ObjectToAsset[_map.getCellValue(i[0], i[1])->getObjectType()]]
		->setPosition(glm::vec3(i[0], 0, i[1]));
	      if (IObject::BOMB == _map.getCellValue(i[0], i[1])->getObjectType())
		{
		  _assets[FLOOR]->setPosition(glm::vec3(i[0], 0, i[1]));
		  _assets[FLOOR]->draw(_shader, _clock);
		}
	      _assets[_ObjectToAsset[_map.getCellValue(i[0], i[1])->getObjectType()]]
		->draw(_shader, _clock);
	    }
	  i[1]++;
	}
      i[0]++;
    }

  y = 0;
  while (y < _stock.getNbPlayer())
    {
      player = dynamic_cast<Player *>(_stock.getPlayer(y));
      if (player->isAlive())
	{
	  _shader.setUniform("color", player->getColor());
	  _assets[PLAYER]->setPosition(player->getPosition());
	  _assets[PLAYER]->setRotation(player->getRotation());
	  _assets[PLAYER]->draw(_shader, _clock);
	}
      y++;
    }
  _shader.setUniform("color", glm::vec4(1.0));
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  _assets[SKYBOX]->scale(glm::vec3(-1));
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->scale(glm::vec3(1));
  _context.flush();
}

}
