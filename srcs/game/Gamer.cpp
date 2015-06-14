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
#include "my_random.hpp"

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
    : _width(10), _height(10), _menu(NULL), _quit(false), _resume(false), _twoPlayers(false), _intro(true), _player1(""), _player2(""), _nbPlayers(6), _spect(NULL), _camera(90.0, 1800, 900), _camera2(90.0, 900, 900)
  {
    _json = new JSONDoc;
    this->init();
  }

  Gamer::Gamer(unsigned int width, unsigned int height, unsigned int widthCam, unsigned int heightCam, bool twoPlayers, std::string const& p1, std::string const& p2, unsigned int nbPlayers)
    : _width(width), _height(height), _menu(NULL),  _quit(false), _resume(false), _twoPlayers(twoPlayers), _intro(false), _player1(p1), _player2(p2), _nbPlayers(nbPlayers), _spect(NULL), _camera(90.0, widthCam, heightCam), _camera2(90.0, widthCam, heightCam)
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
    Player			*player2;

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
    Text2d*	save = new Text2d("Save Game", 200, 100, 800, 75, "resources/assets/textures/alpha3Blue.tga");
    Text2d*	resume = new Text2d("Resume Game", 200, 250, 800, 75, "resources/assets/textures/alpha3Blue.tga");
    Text2d*	quit = new Text2d("Quit Game", 200, 400, 800, 75, "resources/assets/textures/alpha3Blue.tga");
    Text2d*	toggleSounds = new Text2d("Toggle Sounds", 200, 550, 800, 75, "resources/assets/textures/alpha3Blue.tga");
    Text2d*	toggleMusic = new Text2d("Toggle Music", 200, 700, 800, 75, "resources/assets/textures/alpha3Blue.tga");

    _menu = new MenuGrid;
    _menu->addObject(save, [this] (void) {
      //std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
      JSONDoc *j = new JSONDoc;
      j->serialize(*this);
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
    float		elapsedTime = static_cast<float>(clock.getElapsed()) * 60;

    // If the escape key is pressed or if the window has been closed we stop the program
    if (_resume)
      {
	_camera.updateView();
	_resume = false;
	delete _menu;
	_menu = NULL;
      }
    if (!_map->getRcs()->isPlayerOneAlive() && !_map->getRcs()->isPlayerTwoAlive())
      _quit = true;
    if (_quit || _map->hasToQuit())
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
      player = dynamic_cast<Player *>
	(getRcs()->getPlayer(id));
    } while (!player->isAlive() && getRcs()->countAlivePlayers() > 0);
  return player;
}

  void		Gamer::updateCamera()
  {
    Player	*player = dynamic_cast<Player *>(_stock->getPlayer(0));

    if (!player->isAlive())
      {
	if ((!_spect || !_spect->isAlive()) && (_spect = randAlivePlayer()) == NULL)
	  return;
	if (_spect && _spect->isAlive())
	  player = _spect;
      }
    _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
			+ glm::rotate(glm::vec3(2.5, 4, 0),
				      player->getRotation().y + 90,
				      glm::vec3(0, 1, 0)));
    _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
    _camera.updateView();
    if (_twoPlayers)
      {
	player = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));
	if (!player->isAlive())
	  {
	    if ((!_spect || !_spect->isAlive()) && (_spect = randAlivePlayer()) == NULL)
	      return;
	    if (_spect && _spect->isAlive())
	      player = _spect;
	  }
	_camera2.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
			     + glm::rotate(glm::vec3(2.5, 4, 0),
					   player->getRotation().y + 90,
					   glm::vec3(0, 1, 0)));
	_camera2.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
	_camera2.updateView();
      }
  }

  RessourceStock*	Gamer::getRcs() const
  {
    return _stock;
  }

  void			Gamer::updateRandCamera(Player *player)
  {
    _camera.setPosition(player->getPosition() + glm::vec3(-0.5, 0, -0.5)
			+ glm::rotate(glm::vec3(2.5, 4, 0),
				      player->getRotation().y + 90,
				      glm::vec3(0, 1, 0)));
    _camera.setRotation(player->getPosition() + glm::vec3(-0.5, 0, -0.5));
    _camera.updateView();
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
	    tmp = glm::rotate(pos - player->getPosition(), -player->getRotation().y, glm::vec3(0, 1, 0));
	    if (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 15)
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
	drawPlayer = dynamic_cast<Player *>(_stock->getPlayer(i));
	tmp = glm::rotate(drawPlayer->getPosition() - player->getPosition(), -player->getRotation().y, glm::vec3(0, 1, 0));
	if (tmp.x > -20 && tmp.x < 20 && tmp.z > -5 && tmp.z < 15)
	  drawPlayer->draw(*assets[PLAYER], shader, clock);
      }
    shader.setUniform("color", glm::vec4(1.0));
    assets[SKYBOX]->rotate(glm::vec3(1, 0, 0), 0.02);
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

  void		Gamer::drawAll(gdl::Clock &clock, gdl::BasicShader &shader,
			       std::vector<Asset3d*>& assets,
			       std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset)
  {
    if (_twoPlayers)
      glViewport(900, 0, 900, 900);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Player	*player = dynamic_cast<Player *>(_stock->getPlayer(0));

    if (!player->isAlive() && _spect && _spect->isAlive())
      player = _spect;
    draw(clock, shader, _camera, assets, ObjectToAsset, player);
    drawPlayerArme(clock, shader, assets, player, ObjectToAsset);
    if (_twoPlayers)
      {
	Player	*player = dynamic_cast<Player *>(_stock->getPlayer(_stock->getNbPlayer() - 1));

	if (!player->isAlive() && _spect && _spect->isAlive())
	  player = _spect;
	glViewport(0, 0, 900, 900);
	draw(clock, shader, _camera2, assets, ObjectToAsset, player);
	drawPlayerArme(clock, shader, assets, player, ObjectToAsset);
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

    if (!input.getKey(SDLK_RCTRL) && (player = dynamic_cast<Player*>(_stock->getPlayer(0))) != NULL &&
	player->getPutBombStatus())
      player->setPutBombStatus(false);
    if (_twoPlayers && !input.getKey(SDLK_SPACE) &&
	(player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) != NULL &&
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

  bool				Gamer::handleKeyToPause(const float elapsedTime, gdl::Input& input)
  {
    static_cast<void>(elapsedTime);
    static_cast<void>(input);
    pauseMenu();
    return true;
  }

  bool				Gamer::handleKeyToP1PutBomb(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(elapsedTime);
    static_cast<void>(input);
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(0))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    if (!player->getPutBombStatus())
      {
	player->putBomb();
	player->setPutBombStatus(true);
      }
    return true;
  }

  bool				Gamer::handleKeyToP2PutBomb(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(elapsedTime);
    static_cast<void>(input);
    if (!_twoPlayers)
      return true;
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    if (!player->getPutBombStatus())
      {
	player->putBomb();
	player->setPutBombStatus(true);
      }
    return true;
  }

  bool				Gamer::handleKeyToP1Up(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(elapsedTime);
    static_cast<void>(input);
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(0))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->move(player->getRotation().y, elapsedTime);
    return (true);
  }

  bool				Gamer::handleKeyToP1Down(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(input);
    static_cast<void>(elapsedTime);
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(0))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->move(180 + player->getRotation().y, elapsedTime);
    return (true);
  }

  bool				Gamer::handleKeyToP1Left(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    if (input.getKey(SDLK_RIGHT))
      return true;
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(0))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->Player::rotate(true, elapsedTime);
    return true;
  }

  bool				Gamer::handleKeyToP1Right(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    if (input.getKey(SDLK_LEFT))
      return true;
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(0))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->Player::rotate(false, elapsedTime);
    return true;
  }

  bool				Gamer::handleKeyToP2Up(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(input);
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->move(player->getRotation().y, elapsedTime);
    return true;
  }

  bool				Gamer::handleKeyToP2Down(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(input);
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->move(180 + player->getRotation().y, elapsedTime);
    return true;
  }

  bool				Gamer::handleKeyToP2Left(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    static_cast<void>(input);
    if (input.getKey(SDLK_d))
      return true;
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
      throw std::runtime_error("Got a null value instead of a player from RessourceStock");
    player->Player::rotate(true, elapsedTime);
    return true;
  }

  bool				Gamer::handleKeyToP2Right(const float elapsedTime, gdl::Input& input)
  {
    Player*			player;

    if (input.getKey(SDLK_q) || input.getKey(SDLK_a))
      return true;
    if ((player = dynamic_cast<Player*>(_stock->getPlayer(_stock->getNbPlayer() - 1))) == NULL)
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
