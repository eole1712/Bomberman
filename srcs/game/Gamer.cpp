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
  : _width(20), _height(20), _menu(NULL), _quit(false), _resume(false),
    _camera(90.0, 900, 900), _camera2(90.0, 900, 900)
{
  _twoPlayers = true;
  this->init();
}

Gamer::Gamer(unsigned int width, unsigned int height, unsigned int widthCam, unsigned int heightCam, bool twoPlayers, std::string const& p1, std::string const& p2)
  : _width(width), _height(height), _menu(NULL),  _quit(false), _resume(false), _player1(p1),
    _player2(p2), _camera(90.0, widthCam, heightCam), _camera2(90.0, widthCam, heightCam)
{
  _twoPlayers = twoPlayers;
  this->init();
}

Gamer::~Gamer()
{
  if (_map)
    delete (_map);
  if (_stock)
    delete (_stock);
  _json.serialize<Bomberman::MapList>(*_mapList);
  _json.serialize<Bomberman::ScoreList>(*_scoreList);
  _json.writeDown("./resources/json/Gamedata.json");
  delete (_mapList);
  delete (_scoreList);
}

void	Gamer::init()
{
  std::vector<std::string>	nameList = {_player1,
					    _player2};
  std::string			mapName = "Classic Map";
  std::vector<std::string>	vec;
  Player			*player;
  Player			*player2;

  _mapList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json.parse("./resources/json/Gamedata.json"))
	      ? (_json.unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
  _stock = new RessourceStock(nameList, 1, _scoreList);
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
		      + glm::rotate(glm::vec3(2.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  _camera2.setPosition(player2->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(2.5, 4, 0),
				    player2->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera2.setRotation(player2->getPosition() + glm::vec3(-0.5, 0, -0.5));
}

bool		Gamer::pauseMenu()
{
  Text2d*	save = new Text2d("Save Game", 200, 100, 800, 75, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	resume = new Text2d("Resume Game", 200, 250, 800, 75, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	quit = new Text2d("Quit Game", 200, 400, 800, 75, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	toggleSounds = new Text2d("Toggle Sounds", 200, 550, 800, 75, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	toggleMusic = new Text2d("Toggle Music", 200, 700, 800, 75, "resources/assets/textures/alpha3Blue.tga");

  _menu = new MenuGrid;
  _menu->addObject(save, [] (void) {
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
  });
  _menu->addObject(resume, [this] (void) {
    _resume = true;
  });
  _menu->addObject(quit, [this] (void) {
    _quit = true;
  });
  _menu->addObject(toggleSounds, [this] (void) {
    _map->getRcs()->toggleSounds();
  });
  _menu->addObject(toggleMusic, [this] (void) {
    _map->getRcs()->toggleMusic();
  });
  std::cout << "pause" << std::endl;
  return true;
}

bool		Gamer::update(gdl::Clock &clock, gdl::Input &input)
{
  Player	*player = dynamic_cast<Player *>(_stock->getPlayer(0));
  Player	*player2 = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));
  float		elsapsedTime = static_cast<float>(clock.getElapsed()) * 60;
  static bool	space = false;
  static bool	space2 = false;

  // If the escape key is pressed or if the window has been closed we stop the program
  if (_resume)
    {
      _camera.updateView();
      _resume = false;
      delete _menu;
      _menu = NULL;
    }
  if (input.getInput(SDL_QUIT) || _quit)
    return false;
  if (_menu != NULL)
    return _menu->update(clock, input);
  if (input.getKey(SDLK_ESCAPE))
    return pauseMenu();
  if (input.getKey(SDLK_RCTRL) != space && !space)
    player->putBomb();
  space = input.getKey(SDLK_RCTRL);
  if (_twoPlayers && input.getKey(SDLK_SPACE) != space2 && !space2)
    player2->putBomb();
  space2 = input.getKey(SDLK_SPACE);
  if (input.getKey(SDLK_UP) || input.getKey(SDLK_DOWN))
    {
      if (input.getKey(SDLK_UP))
	player->move(player->getRotation().y, elsapsedTime);
      else
	player->move(180 + player->getRotation().y, elsapsedTime);
    }
  if (_twoPlayers && (input.getKey(SDLK_z) || input.getKey(SDLK_s)))
    {
      if (input.getKey(SDLK_z))
	player2->move(player2->getRotation().y, elsapsedTime);
      else
	player2->move(180 + player2->getRotation().y, elsapsedTime);
    }

  if (input.getKey(SDLK_RIGHT) != input.getKey(SDLK_LEFT))
    player->Player::rotate(input.getKey(SDLK_LEFT), elsapsedTime);
  if (_twoPlayers && input.getKey(SDLK_q) != input.getKey(SDLK_d))
    player2->Player::rotate(input.getKey(SDLK_q), elsapsedTime);
  _map->checkBombsOnMap();
  for (unsigned int i = 0; i < _stock->getNbPlayer(); ++i)
    {
      PlayerAI*	ai = NULL;

      if ((ai = dynamic_cast<PlayerAI *>(_stock->getPlayer(i))) != NULL)
	ai->doAction(*_map, elsapsedTime);
    }

  _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(2.5, 4, 0),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  _camera.updateView();
  if (_twoPlayers)
    {
      _camera2.setPosition(player2->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(glm::vec3(2.5, 4, 0),
				    player2->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
      _camera2.setRotation(player2->getPosition() + glm::vec3(-0.5, 0, -0.5));
      _camera2.updateView();
    }
  return true;
}

void		Gamer::draw(gdl::Clock &clock,
			    gdl::BasicShader &shader,
			    CameraObject &camera,
			    std::vector<Asset3d*> &assets,
			    std::map<Bomberman::IObject::Type, mapAsset>& ObjectToAsset,
			    Player *player)
{
  glm::vec3	tmp;
  glm::vec3	pos;
  Player	*drawPlayer;

  // Clear the screen
  shader.bind();
  shader.setUniform("view", camera.getView());
  shader.setUniform("projection", camera.getProjection());
  shader.setUniform("color", glm::vec4(1.0));
  pos.y = 0;
  for (pos.x = -1; pos.x <= _width; pos.x++)
    {
      for (pos.z = -1; pos.z <= _height; pos.z++)
  	{
	  tmp = glm::rotate(pos - player->getPosition(), -player->getRotation().y, glm::vec3(0, 1, 0));
	  if (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 13)
	    {
	      if (pos.x == -1 || pos.z == -1 || pos.x == _width || pos.z == _height)
		{
		  assets[WALL]->setPosition(glm::vec3(pos.x, 0, pos.z));
		  assets[WALL]->draw(shader, clock);
		}
	      else
		{
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->setPosition(pos);
		  if (IObject::MINE <= _map->getCellValue(pos.x, pos.z)->getObjectType() ||
		      IObject::BONUS == _map->getCellValue(pos.x, pos.z)->getObjectType())
		    {
		      assets[FLOOR]->setPosition(pos);
		      assets[FLOOR]->draw(shader, clock);
		    }
		  if (IObject::MINE == _map->getCellValue(pos.x, pos.z)->getObjectType())
		    shader.setUniform("color", glm::vec4(0, 1, 0, 0));
		  tmp = assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->getRotation();
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->setRotation(glm::vec3(0, 0, 0));
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->draw(shader, clock);
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->setRotation(tmp);
		  if (IObject::MINE == _map->getCellValue(pos.x, pos.z)->getObjectType())
		    shader.setUniform("color", glm::vec4(1.0));
		}
	    }
	}
    }
  for (unsigned int i = 0; i < _stock->getNbPlayer(); i++)
    {
      drawPlayer = dynamic_cast<Player *>(_stock->getPlayer(i));
      tmp = glm::rotate(drawPlayer->getPosition() - player->getPosition(), -player->getRotation().y, glm::vec3(0, 1, 0));
      if (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 12)
	drawPlayer->draw(*assets[PLAYER], shader, clock);
    }
  shader.setUniform("color", glm::vec4(1.0));
  assets[SKYBOX]->rotate(glm::vec3(1, 0, 0), 0.02);
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  assets[SKYBOX]->scale(glm::vec3(-1));
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->scale(glm::vec3(1));
  if (_menu)
    _menu->drawNoBack(shader);
}

void			Gamer::drawPlayerArme(gdl::Clock &clock,
					      gdl::BasicShader &shader,
					      std::vector<Asset3d*>&  assets,
					      Player * player,
					      std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)

{
  IObject::Type	type = _stock->getBomb(player->getBombType())->getObjectType();

  if (!player->isAlive() || player->zeroBomb())
    return;
  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 900.0f, 900.0f, 0.0f, -900.0f, 900.0f));

  if (type == IObject::MINE)
    assets[ObjectToAsset[type]]->scale(glm::vec3(-300 * (!_twoPlayers ? 0.60 : 1)));
  else
    assets[ObjectToAsset[type]]->scale(glm::vec3(-100 * (!_twoPlayers ? 0.60  : 1)));
  assets[ObjectToAsset[type]]->setPosition(glm::vec3(820, 820, 0));
  assets[ObjectToAsset[type]]->rotate(glm::vec3(1, 1, 1), 1);
  assets[ObjectToAsset[type]]->draw(shader, clock);
  assets[ObjectToAsset[type]]->setScale(glm::vec3(1));

  for (unsigned int i = 1; i < player->getNbBomb(); i++)
    {
      std::cout << player->getNbBomb() << std::endl;
      double a = (((360 / (player->getNbBomb() - 1)) * (i - 1) ) * M_PI) / 180;
      int x1 = 820 + 50 * cos(a);
      int y1 = 820 + 50 * sin(a);

      assets[ObjectToAsset[type]]->setPosition(glm::vec3(x1, y1, 0));
      assets[ObjectToAsset[type]]->scale(glm::vec3(-35));
      assets[ObjectToAsset[type]]->draw(shader, clock);
      assets[ObjectToAsset[type]]->setScale(glm::vec3(1));
    }
}

void		Gamer::drawAll(gdl::Clock &clock, gdl::BasicShader &shader,
			 std::vector<Asset3d*>& assets,
			 std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)
{
  if (_twoPlayers)
    glViewport(900, 0, 900, 900);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw(clock, shader, _camera, assets, ObjectToAsset, dynamic_cast<Player *>(_stock->getPlayer(0)));
  drawPlayerArme(clock, shader, assets, dynamic_cast<Player *>(_stock->getPlayer(0)), ObjectToAsset);
  if (_twoPlayers)
    {
      glViewport(0, 0, 900, 900);
      draw(clock, shader, _camera2, assets, ObjectToAsset, dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1)));
      drawPlayerArme(clock, shader, assets, dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1)), ObjectToAsset);
    }
}

CameraObject		&Gamer::getCamera(unsigned int i)
{
  if (i == 0)
    return _camera;
  else
    return _camera2;
}

}
