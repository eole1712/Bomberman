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
#include "View2d.hpp"
#include "my_random.hpp"
#include "View2d.hpp"

namespace Bomberman
{

/*
** Static variables
*/
const Gamer::HandleKeyBook	Gamer::handleKeyBook		= Gamer::getHandleKeyBook();
const Gamer::HandleKeyBook	Gamer::handleKeyBookIntro	= Gamer::getHandleKeyBookIntro();

 /*
** Constructor/Destructors
*/
Gamer::Gamer()
  : _width(10), _height(10), _menu(NULL), _quit(false), _resume(false), _twoPlayers(false), _intro(true), _viewMode(true), _player1(""), _player2(""), _nbPlayers(6), _spect(NULL), _camera(90.0, 1800, 900), _camera2(90.0, 900, 900)
{
  _json = new JSONDoc;
  this->init();
}

Gamer::Gamer(unsigned int width, unsigned int height, unsigned int widthCam, unsigned int heightCam, bool twoPlayers, std::string const& p1, std::string const& p2, unsigned int nbPlayers)
  : _width(width), _height(height), _menu(NULL),  _quit(false), _resume(false), _twoPlayers(twoPlayers), _intro(false), _viewMode(true),_player1(p1), _player2(p2), _nbPlayers(nbPlayers), _spect(NULL), _camera(90.0, widthCam, heightCam), _camera2(90.0, widthCam, heightCam)
{
  _json = new JSONDoc;
  this->init();
}

Gamer::~Gamer()
{
  if (_map)
    delete (_map);
  if (_stock)
    delete (_stock);
  _json->serialize<Bomberman::MapList>(*_mapList);
  _json->serialize<Bomberman::ScoreList>(*_scoreList);
  _json->writeDown("./resources/json/Gamedata.json");
  delete (_mapList);
  delete (_scoreList);
  delete _json;
}

void	Gamer::init()
{
  std::vector<std::string>	nameList = {_player1,
					    _player2 };
  std::string			mapName = "Classic Map";
  std::vector<std::string>	vec;
  Player			*player;

  _mapList = ((_json->parse("./resources/json/Gamedata.json"))
	      ? (_json->unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json->parse("./resources/json/Gamedata.json"))
		? (_json->unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
  _stock = new RessourceStock(nameList, _nbPlayers, _scoreList, _twoPlayers, _intro);
  _map = _mapList->getMap(mapName);
  if (_map == NULL)
    _map = new Map("Random", _width, _height, _stock->getNbPlayer(), Map::EASY, _stock);
  for (unsigned int i = 0; i < _stock->getNbPlayer(); ++i)
    {
      player = _stock->getPlayer(i);
      player->initGame(_map);
    }
}

Bomberman::Map*		Gamer::getMap() const
{
  return _map;
}

Bomberman::RessourceStock*	Gamer::getRessourceStock() const
{
  return _stock;
}

  bool		Gamer::pauseMenu()
  {
    View2d*	background = new View2d(0, 0, 1800, 900, "resources/assets/textures/menu_3_background.tga");

    View2d*	resume = new View2d(610, 200, 654, 121, "resources/assets/textures/menu_3_resume.tga");
    View2d*	save = new View2d(610, 610, 654, 121, "resources/assets/textures/menu_3_save.tga");
    View2d*	quit = new View2d(610, 725, 654, 121, "resources/assets/textures/menu_3_quit.tga");
    View2d*	view = new View2d(510, 310, 821, 99, "resources/assets/textures/menu_3_view.tga");
    View2d*	sound = new View2d(510, 410, 821, 99, "resources/assets/textures/menu_3_sound.tga");
    View2d*	music = new View2d(510, 510, 821, 99, "resources/assets/textures/menu_3_music.tga");

    View2d*	viewON = new View2d(1080, 300, 176, 113, "resources/assets/textures/menu_3_3d.tga");
    View2d*	viewOFF = new View2d(1080, 300, 176, 113, "resources/assets/textures/menu_3_2d.tga");
    View2d*	soundON = new View2d(1080, 400, 176, 113, "resources/assets/textures/menu_3_on.tga");
    View2d*	soundOFF = new View2d(1080, 400, 176, 113, "resources/assets/textures/menu_3_off.tga");
    View2d*	musicON = new View2d(1080, 500, 176, 113, "resources/assets/textures/menu_3_on.tga");
    View2d*	musicOFF = new View2d(1080, 500, 176, 113, "resources/assets/textures/menu_3_off.tga");

    viewON->unFocus();
    viewOFF->unFocus();
    soundON->unFocus();
    soundOFF->unFocus();
    musicON->unFocus();
    musicOFF->unFocus();
    background->unFocus();

    musicON->setHidden(!(_map->getRcs()->isPlayingMusic()));
    musicOFF->setHidden((_map->getRcs()->isPlayingMusic()));
    soundON->setHidden(!(_map->getRcs()->isPlayingSounds()));
    soundOFF->setHidden((_map->getRcs()->isPlayingSounds()));

    viewON->setHidden(!_viewMode);
    viewOFF->setHidden(_viewMode);

    _menu = new MenuGrid;
    _menu->addObject(background, [] (void){
      ;
    });
    _menu->addObject(resume, [this] (void) {
	_resume = true;
      });
    _menu->addObject(view, [this, viewON, viewOFF] (void) {
      _viewMode = !_viewMode;
      viewON->setHidden(!_viewMode);
      viewOFF->setHidden(_viewMode);
      });
    _menu->addObject(sound, [this, soundON, soundOFF] (void) {
      _map->getRcs()->toggleSounds();
      soundON->setHidden(!(_map->getRcs()->isPlayingSounds()));
      soundOFF->setHidden((_map->getRcs()->isPlayingSounds()));
    });
    _menu->addObject(music, [this, musicON, musicOFF] (void) {
      _map->getRcs()->toggleMusic();
      musicON->setHidden(!(_map->getRcs()->isPlayingMusic()));
      musicOFF->setHidden((_map->getRcs()->isPlayingMusic()));
    });
    _menu->addObject(viewON, [this] (void) {
	;
      });
    _menu->addObject(viewOFF, [this] (void) {
	;
      });
    _menu->addObject(soundON, [this] (void) {
	;
      });
    _menu->addObject(soundOFF, [this] (void) {
	;
      });
    _menu->addObject(musicON, [this] (void) {
      });
    _menu->addObject(musicOFF, [this] (void) {
      });
    _menu->addObject(save, [this] (void) {
      //std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
      JSONDoc *j = new JSONDoc;
      j->serialize(*this);
    });
    _menu->addObject(quit, [this] (void) {
	_quit = true;
      });
    std::cout << "pause" << std::endl;
    return true;
  }

bool		Gamer::update(gdl::Clock &clock, gdl::Input &input)
{
  float		elapsedTime = static_cast<float>(clock.getElapsed()) * 60;
  static Timer*	endTimer = NULL;

  if (_resume)
    {
      _camera.updateView();
      _resume = false;
      delete _menu;
      _menu = NULL;
    }
  if ((!_map->getRcs()->isPlayerOneAlive() && !_map->getRcs()->isPlayerTwoAlive()) || _map->hasToQuit())
    {
      if (endTimer == NULL)
  	endTimer = new Timer(4000000);
      if (endTimer->isFinished())
  	{
  	  delete endTimer;
  	  _quit = true;
  	}
    }
  if (!_intro && _quit)
    return false;
  if (_menu != NULL)
    return _menu->update(clock, input);
  if (input.getInput(SDL_QUIT) || _quit || !handleKeyEvents(elapsedTime, input))
    return false;
  _map->checkBombsOnMap();
  updateAllAI(elapsedTime);
  updateCamera();
  return true;
}

Player		*Gamer::randAlivePlayer() const
{
  unsigned int	id = 0;
  Player	*player = NULL;

  do
    {
      id = (id + 1) % getRcs()->getNbPlayer();
      player = getRcs()->getPlayer(id);
    } while (!player->isAlive() && getRcs()->countAlivePlayers() > 0);
  return player;
}

void		Gamer::updateCamera()
{
  Player	*player = _stock->getPlayer(0);

  if (!player->isAlive() && player->getDeadTimer()->isFinished())
    {
      if ((!_spect || !_spect->isAlive()) && (_spect = randAlivePlayer()) == NULL)
	return;
      if (_spect && _spect->isAlive())
	player = _spect;
    }
  _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
		      + glm::rotate(((_viewMode) ? glm::vec3(2.5, 4, 0) :
				     glm::vec3(0.0001, 10, 0)),
				    player->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
  _camera.updateView();
  if (_twoPlayers)
    {
      player = _stock->getPlayer(_stock->getNbPlayer() - 1);
      if (!player->isAlive() && player->getDeadTimer()->isFinished())
	{
	  if ((!_spect || !_spect->isAlive()) && (_spect = randAlivePlayer()) == NULL)
	    return;
	  if (_spect && _spect->isAlive())
	    player = _spect;
	}
	_camera2.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
			     + glm::rotate(((_viewMode) ? glm::vec3(2.5, 4, 0) :
					    glm::vec3(0.0001, 10, 0)),
					   player->getRotation().y + 90,
					   glm::vec3(0, 1, 0)));
	_camera2.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
	_camera2.updateView();
    }
}

RessourceStock*		Gamer::getRcs() const
{
  return _stock;
}

void			Gamer::updateRandCamera()
{
  static float	angle = 0;
  static float	y = 50;
  glm::vec3		pos = glm::rotate(glm::vec3(_width, 0, 0), angle, glm::vec3(0, 1, 0));

  pos.y = 8 + y;
  _camera.setPosition(pos + glm::vec3(_width / 2, 0, _height / 2 + 0.001));
  _camera.setRotation(glm::vec3(_width / 2, 0, _height / 2));
  _camera.updateView();
  angle += 0.5;
  if (y > 0)
    y -= 0.3;
}

void		Gamer::updateAllAI(const float elapsedTime)
{
  if (_nbPlayers - (_twoPlayers + 1) > 0)
    _stateMap = AI::StateMap(*_map);
  for (unsigned int i = 0; i < _stock->getNbPlayer() ; ++i)
    {
      PlayerAI*	ai = NULL;

      if ((ai = dynamic_cast<PlayerAI *>(_stock->getPlayer(i))) != NULL)
	ai->doAction(&_stateMap, elapsedTime);
    }
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
	  if (player)
	    tmp = glm::rotate(pos - player->getPosition(),
			      -player->getRotation().y, glm::vec3(0, 1, 0));
	  if (player == NULL
	      || (!_viewMode && tmp.x > -21 && tmp.x < 21 && tmp.z > -21 && tmp.z < 21)
	      || (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 15))
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
		    {
		      glDisable(GL_BLEND);
		      shader.setUniform("color", glm::vec4(0, 1, 0, 0));
		    }
		  tmp = assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->getRotation();
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->setRotation(glm::vec3(0, 0, 0));
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->draw(shader, clock);
		  assets[ObjectToAsset[_map->getCellValue(pos.x, pos.z)->getObjectType()]]
		    ->setRotation(tmp);
		  if (IObject::MINE == _map->getCellValue(pos.x, pos.z)->getObjectType())
		    {
		      glEnable(GL_BLEND);
		      shader.setUniform("color", glm::vec4(1.0));
		    }
		}
	    }
	}
    }
  for (unsigned int i = 0; i < _stock->getNbPlayer(); i++)
    {
      drawPlayer = _stock->getPlayer(i);
      if (player)
	tmp = glm::rotate(drawPlayer->getPosition() - player->getPosition(),
			  -player->getRotation().y, glm::vec3(0, 1, 0));
      if (player == NULL
	  || (!_viewMode && tmp.x > -21 && tmp.x < 21 && tmp.z > -21 && tmp.z < 21)
	  || (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 15))
	drawPlayer->draw(*assets[PLAYER], shader, clock);
    }
  shader.setUniform("color", glm::vec4(1.0));
  assets[SKYBOX]->setRotation(glm::vec3(fmod(assets[SKYBOX]->getRotation().x + 0.02, 360)
					, assets[SKYBOX]->getRotation().y
					, assets[SKYBOX]->getRotation().z));
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  assets[SKYBOX]->scale(glm::vec3(-1));
  assets[SKYBOX]->draw(shader, clock);
  assets[SKYBOX]->scale(glm::vec3(1));
}

void			Gamer::drawPlayerArme(gdl::Clock &clock,
					      gdl::BasicShader &shader,
					      std::vector<Asset3d*>&  assets,
					      Player * player,
					      std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)

{
  IObject::Type	type = _stock->getBomb(player->getBombType())->getObjectType();
  static int		angle = 0;

  if (!player->isAlive() || player->zeroBomb() || player->isParalyzed())
    return;
  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 900.0f, 900.0f, 0.0f, -900.0f, 900.0f));

  if (type == IObject::MINE)
    assets[ObjectToAsset[type]]->scale(glm::vec3(-300 * 0.60));
  else
    assets[ObjectToAsset[type]]->scale(glm::vec3(-100 * 0.60));
  assets[ObjectToAsset[type]]->setPosition(glm::vec3(820, 850, 0));
  assets[ObjectToAsset[type]]->rotate(glm::vec3(1, 1, 1), 1);
  assets[ObjectToAsset[type]]->draw(shader, clock);
  assets[ObjectToAsset[type]]->setScale(glm::vec3(1));

  if (type == IObject::BOMB)
    for (unsigned int i = 1; i < player->getNbBomb(); i++)
      {
	double a = (((360 / (player->getNbBomb() - 1)) * (i - 1) + angle) * M_PI) / 180;
	int x1 = 820 + 50 * cos(a);
	int y1 = 840 + 50 * sin(a);

	assets[ObjectToAsset[type]]->setPosition(glm::vec3(x1, y1, 0));
	assets[ObjectToAsset[type]]->scale(glm::vec3(-35));
	assets[ObjectToAsset[type]]->draw(shader, clock);
	assets[ObjectToAsset[type]]->setScale(glm::vec3(1));
      }
  angle = (angle + 1) % 360;
}

void		Gamer::drawEndWin(gdl::BasicShader &shader, Player *player)
{
  if (!player->isAlive() || !_map->hasToQuit() || _map->getRcs()->getWinner() != player)
    return;

  View2d*	win = !_twoPlayers ?
    new View2d(0, 0, 1800, 900, "resources/assets/textures/win1p.tga") :
    new View2d(0, 0, 900, 900, "resources/assets/textures/win2p.tga");

  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 1800.0f / (_twoPlayers ? 2 : 1), 900.0f, 0.0f, -1000.0f, 1000.0f));
  win->draw(shader);
}

void		Gamer::drawEndGame(gdl::BasicShader &shader, Player *player)
{
  if (player->isAlive() || player->getDeadTimer()->isFinished())
    return drawEndWin(shader, player);

  View2d*	lose = !_twoPlayers ?
    new View2d(0, 0, 1800, 900, "resources/assets/textures/lose1p.tga") :
    new View2d(0, 0, 900, 900, "resources/assets/textures/lose2p.tga");

  shader.setUniform("view", glm::mat4());
  shader.setUniform("projection", glm::ortho(0.0f, 1800.0f / (_twoPlayers ? 2 : 1), 900.0f, 0.0f, -1000.0f, 1000.0f));
  lose->draw(shader);
}

void		Gamer::drawAll(gdl::Clock &clock, gdl::BasicShader &shader,
			       std::vector<Asset3d*>& assets,
			       std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)
{
  if (_twoPlayers)
    glViewport(900, 0, 900, 900);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Player	*player = _stock->getPlayer(0);

  if (!player->isAlive() && _spect && _spect->isAlive() && player->getDeadTimer()->isFinished())
    player = _spect;
  draw(clock, shader, _camera, assets, ObjectToAsset, player);
  drawPlayerArme(clock, shader, assets, player, ObjectToAsset);
  drawEndGame(shader, player);
  if (_twoPlayers)
    {
      Player	*player = _stock->getPlayer(_stock->getNbPlayer() - 1);

      if (!player->isAlive() && _spect && _spect->isAlive() && player->getDeadTimer()->isFinished())
	player = _spect;
      glViewport(0, 0, 900, 900);
      draw(clock, shader, _camera2, assets, ObjectToAsset, player);
      drawPlayerArme(clock, shader, assets, player, ObjectToAsset);
      drawEndGame(shader, player);
    }
  glViewport(0, 0, 1800, 900);
  if (_menu)
    _menu->drawNoBack(shader);
}

CameraObject		&Gamer::getCamera(unsigned int i)
{
  if (i == 0)
    return _camera;
  return _camera2;
}

/*
** Key handlers
*/
bool				Gamer::handleKeyEvents(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  if (!input.getKey(SDLK_RCTRL) && (player = (_stock->getPlayer(0))) != NULL &&
      player->getPutBombStatus())
    player->setPutBombStatus(false);
  if (_twoPlayers && !input.getKey(SDLK_SPACE) &&
      (player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) != NULL &&
      player->getPutBombStatus())
    player->setPutBombStatus(false);

  HandleKeyBook	const	*book = (_intro) ?  &handleKeyBookIntro : &handleKeyBook;

  for (HandleKeyBook::const_iterator it = book->begin(); it != book->end(); ++it)
    {
      if (input.getKey(it->first) && (this->*(it->second))(elapsedTime, input) == false)
	return false;
    }
  return true;
}

bool				Gamer::handleKeyToPause(const float, gdl::Input&)
{
  pauseMenu();
  return true;
}

bool				Gamer::handleKeyToP1PutBomb(const float, gdl::Input&)
{
  Player*			player;

  if ((player = (_stock->getPlayer(0))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  if (!player->getPutBombStatus())
    {
      player->putBomb();
      player->setPutBombStatus(true);
    }
  return true;
}

bool				Gamer::handleKeyToP2PutBomb(const float, gdl::Input&)
{
  Player*			player;

  if (!_twoPlayers)
    return true;
  if ((player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  if (!player->getPutBombStatus())
    {
      player->putBomb();
      player->setPutBombStatus(true);
    }
  return true;
}

bool				Gamer::handleKeyToP1Up(const float elapsedTime, gdl::Input&)
{
  Player*			player;

  if ((player = (_stock->getPlayer(0))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->move(player->getRotation().y, elapsedTime);
  return (true);
}

bool				Gamer::handleKeyToP1Down(const float  elapsedTime, gdl::Input&)
{
  Player*			player;

  if ((player = (_stock->getPlayer(0))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->move(180 + player->getRotation().y, elapsedTime);
  return (true);
}

bool				Gamer::handleKeyToP1Left(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  if (input.getKey(SDLK_RIGHT))
    return true;
  if ((player = (_stock->getPlayer(0))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->Player::rotate(true, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToP1Right(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  if (input.getKey(SDLK_LEFT))
    return true;
  if ((player = (_stock->getPlayer(0))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->Player::rotate(false, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToP2Up(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  static_cast<void>(input);
  if ((player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->move(player->getRotation().y, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToP2Down(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  static_cast<void>(input);
  if ((player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->move(180 + player->getRotation().y, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToP2Left(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  if (input.getKey(SDLK_d))
    return true;
  if ((player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->Player::rotate(true, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToP2Right(const float elapsedTime, gdl::Input& input)
{
  Player*			player;

  if (input.getKey(SDLK_q) || input.getKey(SDLK_a))
    return true;
  if ((player = (_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
    throw std::runtime_error("Got a null value instead of a player from RessourceStock");
  player->Player::rotate(false, elapsedTime);
  return true;
}

bool				Gamer::handleKeyToQuit(const float, gdl::Input& input)
{
  if (input.getKey(SDLK_ESCAPE) || input.getKey(SDLK_SPACE))
    return false;
  return true;
}

/*
** Static member functions
*/
Gamer::HandleKeyBook	Gamer::getHandleKeyBook()
{
  HandleKeyBook	book;

  book[SDLK_ESCAPE] = &Gamer::handleKeyToPause;
  book[SDLK_RCTRL] = &Gamer::handleKeyToP1PutBomb;
  book[SDLK_n] = &Gamer::handleKeyToP1PutBomb;
  book[SDLK_SPACE] = &Gamer::handleKeyToP2PutBomb;
  book[SDLK_UP] = &Gamer::handleKeyToP1Up;
  book[SDLK_DOWN] = &Gamer::handleKeyToP1Down;
  book[SDLK_LEFT] = &Gamer::handleKeyToP1Left;
  book[SDLK_RIGHT] = &Gamer::handleKeyToP1Right;
  book[SDLK_w] = &Gamer::handleKeyToP2Up;
  book[SDLK_z] = &Gamer::handleKeyToP2Up;
  book[SDLK_s] = &Gamer::handleKeyToP2Down;
  book[SDLK_a] = &Gamer::handleKeyToP2Left;
  book[SDLK_q] = &Gamer::handleKeyToP2Left;
  book[SDLK_d] = &Gamer::handleKeyToP2Right;
  return book;
}

Gamer::HandleKeyBook	Gamer::getHandleKeyBookIntro()
{
  HandleKeyBook	book;

  book[SDLK_ESCAPE] = &Gamer::handleKeyToQuit;
  book[SDLK_SPACE] = &Gamer::handleKeyToQuit;
  return book;
}
}
