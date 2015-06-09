#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "Game.hpp"
#include "Asset3d.hpp"
#include "Animation.hpp"
#include "RessourceStock.hpp"
#include "Map.hpp"
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffParalyzed.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "PlayerAI.hpp"
#include "JSONDoc.hpp"

namespace Bomberman
{

Game::Game()
  : _width(20), _height(20), _camera(90.0, 1000, 1000), _camera2(90.0, 1000, 1000), _speed(70)
{

  _mapList = ((_json.parse("./resources/json/Maplist.json"))
	      ? (_json.unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json.parse("./resources/json/Scores.json"))
	      ? (_json.unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
  _stock = new RessourceStock(std::vector<std::string> {"Adrien", "Jean", "grigri", "4"}, &_scoreList);
  _map = new Map("blibi", _width, _height, _stock->getNbPlayer(), Map::EASY, _stock);
  _change = false;
}

Game::Game(const unsigned int & width, const unsigned int & height)
  : _width(width), _height(height), _camera(90.0, 900, 900), _camera2(90.0, 900, 900), _speed(70)
{
  if (_json.parse("./resources/json/Scores.json"))
    _scoreList = _json.unserialize<Bomberman::ScoreList>();
  _stock = new RessourceStock(std::vector<std::string> {"Adrien", "Jean", "grigri", "4"}, &_scoreList);
  _map = new Map("blibi", _width, _height, _stock->getNbPlayer(), Map::EASY, _stock);
  _change = false;
}

Game::~Game()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
    delete (*i);
  _json.serialize<Bomberman::ScoreList>(_scores);
  _json.writeDown("./resources/json/Scores.json");
}

bool				Game::initialize()
{
  // std::vector<std::string>	vec;
  // Player			*player;

  // if (!_context.start(_camera._width, _camera._height, "My bomberman!"))
  //   return false;
  // glEnable(GL_DEPTH_TEST);
  // glShadeModel(GL_SMOOTH);

  // // We create a shader
  // if (!_shader.load("resources/shaders/basic.fp", GL_FRAGMENT_SHADER)
  //     || !_shader.load("resources/shaders/basic.vp", GL_VERTEX_SHADER)
  //     || !_shader.build())
  //   return false;

  // attachObject(new Asset3d("resources/assets/floor.obj"));
  // attachObject(new Asset3d("resources/assets/idst_block.obj"));
  // attachObject(new Asset3d("resources/assets/idst_block.obj"));
  // attachObject(new Asset3d("resources/assets/dst_block.obj"));
  // attachObject(new Asset3d("resources/assets/fire.obj"));
  // attachObject(new Asset3d("resources/assets/marvin.fbx"));
  // _assets[PLAYER]->scale(glm::vec3(0.002));
  // _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  // //_assets[PLAYER]->createSubAnim(0, "start", 10, 28);
  // //_assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  // //_assets[PLAYER]->createSubAnim(0, "end", 55, 130);
  // attachObject(new Asset3d("resources/assets/barrel.obj"));
  // _assets[BOMB]->scale(glm::vec3(0.06));
  // _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
  // attachObject(new Asset3d("resources/assets/sky.obj"));
  // _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  // _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, 0, _height / 2));
  // attachObject(new Asset3d("resources/assets/bonus.obj"));
  // _assets[BONUS]->scale(glm::vec3(0.05));


  // _ObjectToAsset[IObject::BOMB] = BOMB;
  // _ObjectToAsset[IObject::BOMB2] = FLOOR;
  // _ObjectToAsset[IObject::PLAYER] = PLAYER;
  // _ObjectToAsset[IObject::BONUS] = BONUS;
  // _ObjectToAsset[IObject::WALL] = IDST_BLOCK;
  // _ObjectToAsset[IObject::DESTROYABLEWALL] = DST_BLOCK;
  // _ObjectToAsset[IObject::SPAWN] = FLOOR;
  // _ObjectToAsset[IObject::EMPTY] = FLOOR;
  // _ObjectToAsset[IObject::FIRE] = FIRE;
  // _shader.bind();

  // for (unsigned int i = 0; i < _stock.getNbPlayer(); ++i)
  //   {
  //     player = dynamic_cast<Player *>(_stock.getPlayer(i));
  //     player->initGame(&_map);
  //     player->animation = new Animation(_assets[PLAYER]->getAnimationFrame(),
  // 					_assets[PLAYER]->getAnimationSpeed());
  //   }
  // player = dynamic_cast<Player *>(_stock.getPlayer(0));
  // _camera.setPosition(player->getPosition()
  // 		      + glm::rotate(glm::vec3(3.5, 4, 0),
  // 				    player->getRotation().y + 90,
  // 				    glm::vec3(0, 1, 0)));
  // _camera.setRotation(player->getPosition());

  return true;
}

bool				Game::initialize2()
{
  std::vector<std::string>	vec;
  Player			*player;
  Player			*player2;

  // if (!_context3.start(_camera._width, _camera._height, "My bomberman!"))
  //   return false;
  if (!_context.start(_camera._width, _camera._height, "My bomberman!"))
    return false;
  win = _context._window;
  if (!_context2.start(_camera._width, _camera._height, "My bomberman!"))
    return false;
  // _context2._window = _context._window;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // We create a shader
  if (!_shader.load("resources/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("resources/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;
  if (!_shader2.load("resources/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader2.load("resources/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader2.build())
    return false;

  attachObject(new Asset3d("resources/assets/floor.obj"));
  attachObject(new Asset3d("resources/assets/idst_block.obj"));
  attachObject(new Asset3d("resources/assets/idst_block.obj"));
  attachObject(new Asset3d("resources/assets/dst_block.obj"));
  attachObject(new Asset3d("resources/assets/fire.obj"));
  attachObject(new Asset3d("resources/assets/marvin.fbx"));
  _assets[PLAYER]->scale(glm::vec3(0.002));
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  //_assets[PLAYER]->createSubAnim(0, "start", 10, 28);
  //_assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  //_assets[PLAYER]->createSubAnim(0, "end", 55, 130);
  attachObject(new Asset3d("resources/assets/barrel.obj"));
  _assets[BOMB]->scale(glm::vec3(0.06));
  _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
  attachObject(new Asset3d("resources/assets/sky.obj"));
  _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, 0, _height / 2));
  attachObject(new Asset3d("resources/assets/bonus.obj"));
  _assets[BONUS]->scale(glm::vec3(0.05));


  _ObjectToAsset[IObject::BOMB] = BOMB;
  _ObjectToAsset[IObject::BOMB2] = FLOOR;
  _ObjectToAsset[IObject::PLAYER] = PLAYER;
  _ObjectToAsset[IObject::BONUS] = BONUS;
  _ObjectToAsset[IObject::WALL] = IDST_BLOCK;
  _ObjectToAsset[IObject::DESTROYABLEWALL] = DST_BLOCK;
  _ObjectToAsset[IObject::SPAWN] = FLOOR;
  _ObjectToAsset[IObject::EMPTY] = FLOOR;
  _ObjectToAsset[IObject::FIRE] = FIRE;
  _shader.bind();
  _shader2.bind();

  for (unsigned int i = 0; i < _stock->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(_stock->getPlayer(i));
      player->initGame(_map);
      player->animation = new Animation(_assets[PLAYER]->getAnimationFrame(),
					_assets[PLAYER]->getAnimationSpeed());
    }
  player = dynamic_cast<Player *>(_stock->getPlayer(0));
  player2 = dynamic_cast<Player *>(_stock->getPlayer(1));
  _camera.setPosition(player->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition());
  _camera2.setPosition(player2->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player2->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera2.setRotation(player2->getPosition());
  return true;
}

void		Game::attachObject(Asset3d *obj)
{
  _assets.push_back(obj);
}

bool		Game::update()
{
  Player	*player = dynamic_cast<Player *>(_stock->getPlayer(0));
  Player	*player2 = dynamic_cast<Player *>(_stock->getPlayer(1));
  float		elsapsedTime = static_cast<float>(_clock2.getElapsed()) * 60;
  static bool	space = false;
  static bool	space2 = false;

  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_input2.getKey(SDLK_ESCAPE) || _input2.getInput(SDL_QUIT))
    return false;

  if (_input.getKey(SDLK_KP_0) || _input2.getKey(SDLK_KP_0))
    {
      if (space)
	player->putBomb();
      space = !space;
    }
  if (_input.getKey(SDLK_SPACE) || _input2.getKey(SDLK_SPACE))
    {
      if (space2)
	player2->putBomb();
      space2 = !space2;
    }

  if (_input.getKey(SDLK_UP) || _input.getKey(SDLK_DOWN) ||
      _input2.getKey(SDLK_UP) || _input2.getKey(SDLK_DOWN))
    {
      if (_input.getKey(SDLK_UP) || _input2.getKey(SDLK_UP))
	player->move(player->getRotation().y, elsapsedTime);
      else
	player->move(180 + player->getRotation().y, elsapsedTime);
      _camera.setRotation(player->getPosition());
      _camera.updateView();
    }
  if (_input.getKey(SDLK_z) || _input.getKey(SDLK_s) ||
      _input2.getKey(SDLK_z) || _input2.getKey(SDLK_s))
    {
      if (_input.getKey(SDLK_z) || _input2.getKey(SDLK_z))
	player2->move(player2->getRotation().y, elsapsedTime);
      else
	player2->move(180 + player2->getRotation().y, elsapsedTime);
    }
  if ((_input.getKey(SDLK_RIGHT) || _input2.getKey(SDLK_RIGHT)) ||
      (_input.getKey(SDLK_LEFT) || _input2.getKey(SDLK_LEFT)))
    player->Player::rotate(_input.getKey(SDLK_LEFT), elsapsedTime);
  if (_input.getKey(SDLK_q) || _input.getKey(SDLK_d) ||
      _input2.getKey(SDLK_q) || _input2.getKey(SDLK_d))
    player2->Player::rotate(_input.getKey(SDLK_q) || _input2.getKey(SDLK_q), elsapsedTime);
  _map->checkBombsOnMap();
  _camera.setPosition(player->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition());
  _camera2.setPosition(player2->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player2->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera2.setRotation(player2->getPosition());
  _camera.updateView();
  _camera2.updateView();
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  _context2.updateClock(_clock2);
  _context2.updateInputs(_input2);
  return true;
}

void		Game::draw() {}

void		Game::draw(gdl::SdlContext &context, gdl::Clock &clock, gdl::BasicShader &shader, CameraObject &camera)
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  shader.setUniform("view", camera.getView());
  shader.setUniform("projection", camera.getProjection());
  shader.setUniform("color", glm::vec4(1.0));

  // We draw all objects
  for (int x = -1; x <= _width; x++)
    {
      for (int y = -1; y <= _height; y++)
	{
	  if (x == -1 || y == -1 || x == _width || y == _height)
	    {
	      _assets[WALL]->setPosition(glm::vec3(x, 0, y));
	      _assets[WALL]->draw(shader, clock);
	    }
	  else
	    {
	      _assets[_ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
		->setPosition(glm::vec3(x, 0, y));
	      if (IObject::BOMB == _map->getCellValue(x, y)->getObjectType() ||
		  IObject::BONUS == _map->getCellValue(x, y)->getObjectType())
		{
		  _assets[FLOOR]->setPosition(glm::vec3(x, 0, y));
		  _assets[FLOOR]->draw(shader, clock);
		}
	      else if (IObject::BOMB2 == _map->getCellValue(x, y)->getObjectType())
		{
		  shader.setUniform("color", glm::vec4(0, 1, 0, 0));
		}
	      _assets[_ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
		->draw(shader, clock);
	      shader.setUniform("color", glm::vec4(1.0));
	    }
	}
    }

  for (unsigned int y = 0; y < _stock->getNbPlayer(); y++)
    {
      dynamic_cast<Player *>(_stock->getPlayer(y))->draw(*_assets[PLAYER], shader, clock);
    }
  shader.setUniform("color", glm::vec4(1.0));
  _assets[SKYBOX]->draw(shader, clock);
  _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  _assets[SKYBOX]->scale(glm::vec3(-1));
  _assets[SKYBOX]->draw(shader, clock);
  _assets[SKYBOX]->scale(glm::vec3(1));
  context.flush();
}

// void		Game::draw()
// {
//   // Clear the screen
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   _shader.bind();
//   _shader2.bind();
//   _shader.setUniform("view", _camera.getView());
//   _shader2.setUniform("view", _camera2.getView());
//   _shader.setUniform("projection", _camera.getProjection());
//   _shader2.setUniform("projection", _camera2.getProjection());
//   _shader.setUniform("color", glm::vec4(1.0));
//   _shader2.setUniform("color", glm::vec4(1.0));

//   // We draw all objects
//   for (int x = -1; x <= _width; x++)
//     {
//       for (int y = -1; y <= _height; y++)
// 	{
// 	  if (x == -1 || y == -1 || x == _width || y == _height)
// 	    {
// 	      _assets[WALL]->setPosition(glm::vec3(x, 0, y));
// 	      _assets[WALL]->draw(_shader, _clock);
// 	      _assets[WALL]->draw(_shader2, _clock2);
// 	    }
// 	  else
// 	    {
// 	      _assets[_ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
// 		->setPosition(glm::vec3(x, 0, y));
// 	      if (IObject::BOMB == _map->getCellValue(x, y)->getObjectType() ||
// 		  IObject::BONUS == _map->getCellValue(x, y)->getObjectType())
// 		{
// 		  _assets[FLOOR]->setPosition(glm::vec3(x, 0, y));
// 		  _assets[FLOOR]->draw(_shader, _clock);
// 		  _assets[FLOOR]->draw(_shader2, _clock2);
// 		}
// 	      else if (IObject::BOMB2 == _map->getCellValue(x, y)->getObjectType())
// 		{
// 		  _shader.setUniform("color", glm::vec4(0, 1, 0, 0));
// 		  _shader2.setUniform("color", glm::vec4(0, 1, 0, 0));
// 		}
// 	      _assets[_ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
// 		->draw(_shader, _clock);
// 	      _assets[_ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
// 		->draw(_shader2, _clock2);
// 	      _shader.setUniform("color", glm::vec4(1.0));
// 	      _shader2.setUniform("color", glm::vec4(1.0));
// 	    }
// 	}
//     }
//   for (unsigned int y = 0; y < _stock.getNbPlayer(); y++)
//     {
//       dynamic_cast<Player *>(_stock.getPlayer(y))->draw(*_assets[PLAYER], _shader, _clock);
//       dynamic_cast<Player *>(_stock.getPlayer(y))->draw(*_assets[PLAYER], _shader2, _clock2);
//     }
// =======

//   for (unsigned int y = 0; y < _stock->getNbPlayer(); y++)
//     dynamic_cast<Player *>(_stock->getPlayer(y))->draw(*_assets[PLAYER], _shader, _clock);
// >>>>>>> 448902fff79b428789b8c008d51134515d5d5813

//   _shader.setUniform("color", glm::vec4(1.0));
//   _shader2.setUniform("color", glm::vec4(1.0));
//   _assets[SKYBOX]->draw(_shader, _clock);
//   _assets[SKYBOX]->draw(_shader2, _clock2);
//   _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
//   _assets[SKYBOX]->scale(glm::vec3(-1));
//   _assets[SKYBOX]->draw(_shader, _clock);
//   _assets[SKYBOX]->draw(_shader2, _clock2);
//   _assets[SKYBOX]->scale(glm::vec3(1));
//   // _context.flush();
//   // _context2.flush();
// }

void		Game::change()
{
  if (_change)
    SDL_GL_MakeCurrent(_context._window, _context2._glContext);
  else
    SDL_GL_MakeCurrent(_context2._window, _context2._glContext);
  _change = !_change;
}

gdl::SdlContext		&Game::getContext(unsigned int i)
{
  if (i == 0)
    return _context;
  else
    return _context2;
}

gdl::Clock		&Game::getClock(unsigned int i)
{
  if (i == 0)
    return _clock;
  else
    return _clock2;
}

gdl::BasicShader	&Game::getShader(unsigned int i)
{
  if (i == 0)
    return _shader;
  else
    return _shader2;
}

CameraObject		&Game::getCamera(unsigned int i)
{
  if (i == 0)
    return _camera;
  else
    return _camera2;
}

}
