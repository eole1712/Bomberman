#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>
#include "SdlContext.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "Asset3d.hpp"
#include "Animation.hpp"
#include "RessourceStock.hpp"
#include "Map.hpp"
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffParalyzed.hpp"
#include "Player.hpp"
#include "PlayerAI.hpp"
#include "JSONDoc.hpp"
#include "Gamer.hpp"
#include "Core.hpp"

namespace Bomberman
{

Gamer::Gamer()
  : _width(20), _height(20), _camera(90.0, 900, 900), _camera2(90.0, 900, 900)
{
  std::vector<std::string>	nameList = {"Player 1",
					    "Player 2",
					    "Player 3",
					    "Player 4"};

  std::string			mapName = "de_bra";
  std::vector<std::string>	vec;
  Player			*player;
  Player			*player2;

  _mapList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
  _stock = new RessourceStock(nameList, _scoreList);
  _map = _mapList->getMap(mapName);
  if (_map == NULL)
    _map = new Map("Random", _width, _height, _stock->getNbPlayer(), Map::EASY, _stock);

  for (unsigned int i = 0; i < _stock->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(_stock->getPlayer(i));
      player->initGame(_map);
    }
  player = dynamic_cast<Player *>(_stock->getPlayer(0));
  player2 = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));
  _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  _camera2.setPosition(player2->getPosition() + glm::vec3(-0.5, 0, -0.5)
		       + glm::rotate(glm::vec3(3.5, 4, 0),
				     player2->getRotation().y + 90,
				     glm::vec3(0, 1, 0)));
  _camera2.setRotation(player2->getPosition() + glm::vec3(-0.5, 0, -0.5));
}

Gamer::Gamer(unsigned int width, unsigned int height, unsigned int widthCam, unsigned int heightCam)
  : _width(width), _height(height), _camera(90.0, widthCam, heightCam),
    _camera2(90.0, widthCam, heightCam)
{
  std::vector<std::string>	nameList = {"Player 1",
					    "Player 2",
					    "Player 3",
					    "Player 4"};

  std::string			mapName = "de_bra";
  std::vector<std::string>	vec;
  Player			*player;
  Player			*player2;

  _mapList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
  _stock = new RessourceStock(nameList, _scoreList);
  _map = _mapList->getMap(mapName);
  if (_map == NULL)
    _map = new Map("Random", _width, _height, _stock->getNbPlayer(), Map::EASY, _stock);

  for (unsigned int i = 0; i < _stock->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(_stock->getPlayer(i));
      player->initGame(_map);
    }
  player = dynamic_cast<Player *>(_stock->getPlayer(0));
  player2 = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));
  _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  _camera2.setPosition(player2->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player2->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera2.setRotation(player2->getPosition() + glm::vec3(-0.5, 0, -0.5));
}

Gamer::~Gamer()
{
  delete (_map);
  delete (_stock);
  _json.serialize<Bomberman::MapList>(*_mapList);
  _json.writeDown("./resources/json/Gamedata.json");
  delete (_mapList);
  _json.serialize<Bomberman::ScoreList>(*_scoreList);
  _json.writeDown("./resources/json/Gamedata.json");
  delete (_scoreList);
}

bool		Gamer::update(gdl::Clock &clock, gdl::Input &input)
{
  PlayerAI	*player = dynamic_cast<PlayerAI *>(_stock->getPlayer(0));
  Player	*player2 = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));
  float		elsapsedTime = static_cast<float>(clock.getElapsed()) * 60;
  static bool	space = false;
  static bool	space2 = false;

  // If the escape key is pressed or if the window has been closed we stop the program
  if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
    return false;

  if (input.getKey(SDLK_RCTRL))
    {
      if (space)
	player->putBomb();
      space = !space;
    }
  if (input.getKey(SDLK_SPACE))
    {
      if (space2)
	player2->putBomb();
      space2 = !space2;
    }

  if (input.getKey(SDLK_UP) || input.getKey(SDLK_DOWN))
    {
      if (input.getKey(SDLK_UP))
	player->move(player->getRotation().y, elsapsedTime);
      else
	player->move(180 + player->getRotation().y, elsapsedTime);
    }

  if (input.getKey(SDLK_z) || input.getKey(SDLK_s))
    {
      if (input.getKey(SDLK_z))
	player2->move(player2->getRotation().y, elsapsedTime);
      else
	player2->move(180 + player2->getRotation().y, elsapsedTime);
    }

  if (input.getKey(SDLK_RIGHT) != input.getKey(SDLK_LEFT))
    player->Player::rotate(input.getKey(SDLK_LEFT), elsapsedTime);
  if (input.getKey(SDLK_q) != input.getKey(SDLK_d))
    player2->Player::rotate(input.getKey(SDLK_q), elsapsedTime);

  _map->checkBombsOnMap();
  player->doAction(*_map, elsapsedTime);
  _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  // _camera2.setPosition(player2->getPosition()
  // 		      + glm::rotate(glm::vec3(3.5, 4, 0),
  // 				    player2->getRotation().y + 90,
  // 				    glm::vec3(0, 1, 0)));
  // _camera2.setRotation(player2->getPosition());
  _camera.updateView();
  // _camera2.updateView();
  return true;
}

void		Gamer::draw(gdl::Clock &clock,
			    gdl::BasicShader &shader,
			    CameraObject &camera,
			    std::vector<Asset3d*> &assets,
			    std::map<Bomberman::IObject::Type, mapAsset>& ObjectToAsset)
{
  // Clear the screen
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
	      assets[WALL]->setPosition(glm::vec3(x, 0, y));
	      assets[WALL]->draw(shader, clock);
	    }
	  else
	    {
	      assets[ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
		->setPosition(glm::vec3(x, 0, y));
	      if (IObject::MINE <= _map->getCellValue(x, y)->getObjectType() ||
		  IObject::BONUS == _map->getCellValue(x, y)->getObjectType())
		{
		  assets[FLOOR]->setPosition(glm::vec3(x, 0, y));
		  assets[FLOOR]->draw(shader, clock);
		}
	      if (IObject::MINE == _map->getCellValue(x, y)->getObjectType())
		shader.setUniform("color", glm::vec4(0, 1, 0, 0));
	      assets[ObjectToAsset[_map->getCellValue(x, y)->getObjectType()]]
		->draw(shader, clock);
	      if (IObject::MINE == _map->getCellValue(x, y)->getObjectType())
		shader.setUniform("color", glm::vec4(1.0));
	    }
	}
    }

  for (unsigned int y = 0; y < _stock->getNbPlayer(); y++)
    {
      dynamic_cast<Player *>(_stock->getPlayer(y))->draw(*assets[PLAYER], shader, clock);
    }
  shader.setUniform("color", glm::vec4(1.0));
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  assets[SKYBOX]->scale(glm::vec3(-1));
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->scale(glm::vec3(1));
}

void		Gamer::drawAll(gdl::Clock &clock, gdl::BasicShader &shader,
			 std::vector<Asset3d*>& assets,
			 std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)
{
  // glViewport(900, 0, 900, 900);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw(clock, shader, _camera, assets, ObjectToAsset);
  // glViewport(0, 0, 900, 900);
  // draw(clock, shader, _camera2, assets, ObjectToAsset);
}

CameraObject		&Gamer::getCamera(unsigned int i)
{
  if (i == 0)
    return _camera;
  else
    return _camera2;
}

}
