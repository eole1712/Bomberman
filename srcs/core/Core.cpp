#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <iostream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "Gamer.hpp"
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
#include "MenuGrid.hpp"
#include "Text2d.hpp"
#include "View2d.hpp"
#include "Core.hpp"
#include "StringConversion.hpp"
#include "my_random.hpp"

namespace Bomberman
{

Core::Core()
  : _change(false), _width(1800), _height(900)
{
  _status = false;
}

Core::Core(const unsigned int & width, const unsigned int & height)
  : _change(false), _width(width), _height(height)
{
  _status = false;
}

Core::~Core()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
    delete (*i);
  delete _game;
}

void				Core::loadTextures()
{
  attachObject(new Asset3d("resources/assets/floor.obj"));
  attachObject(new Asset3d("resources/assets/idst_block.obj"));
  attachObject(new Asset3d("resources/assets/idst_block.obj"));
  attachObject(new Asset3d("resources/assets/dst_block.obj"));
  attachObject(new Asset3d("resources/assets/fire.obj"));
  attachObject(new Asset3d("resources/assets/marvin.fbx"));
  attachObject(new Asset3d("resources/assets/bombs/FireBomb/Bomb.obj"));
  attachObject(new Asset3d("resources/assets/sky.obj"));
  attachObject(new Asset3d("resources/assets/bonus.obj"));
  attachObject(new Asset3d("resources/assets/barrel.obj"));
  attachObject(new Asset3d("resources/assets/bombs/LandMine/LandMine.obj"));
  attachObject(new Asset3d("resources/assets/bombs/WindBomb/WindBomb.obj"));

  _assets[PLAYER]->scale(glm::vec3(0.002));
  // _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
  // _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  // _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, 0, _height / 2));
  // _assets[SKYBOX]->scale(glm::vec3(5 * ( + 30) / 2));
  // _assets[SKYBOX]->setPosition(glm::vec3(30 / 2, 0, 30 / 2));
  _assets[BONUS]->scale(glm::vec3(0.05));
  // _assets[BOMB]->scale(glm::vec3(100));
  // _assets[BOMB]->translate(glm::vec3(750, 750, 0));
  // _assets[MINE]->scale(glm::vec3(100));
  // _assets[MINE]->translate(glm::vec3(150, 150 , 0));
  // _assets[VIRUS]->scale(glm::vec3(100));
  // _assets[VIRUS]->translate(glm::vec3(150, 150 , 0));
  // _assets[BARREL]->scale(glm::vec3(100));
  // _assets[BARREL]->translate(glm::vec3(150, 150 , 0));

  _ObjectToAsset[IObject::BOMB] = BOMB;
  _ObjectToAsset[IObject::MINE] = MINE;
  _ObjectToAsset[IObject::BARREL] = BARREL;
  _ObjectToAsset[IObject::VIRUS] = VIRUS;
  _ObjectToAsset[IObject::PLAYER] = PLAYER;
  _ObjectToAsset[IObject::BONUS] = BONUS;
  _ObjectToAsset[IObject::WALL] = IDST_BLOCK;
  _ObjectToAsset[IObject::DESTROYABLEWALL] = DST_BLOCK;
  _ObjectToAsset[IObject::SPAWN] = FLOOR;
  _ObjectToAsset[IObject::EMPTY] = FLOOR;
  _ObjectToAsset[IObject::FIRE] = FIRE;
}

bool				Core::initialize()
{
  if (!_context.start(_width, _height, "Bomberman !"))
    return false;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  if (!_shader.load("resources/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("resources/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;
  _shader.bind();
  _shader.setUniform("color", glm::vec4(1.0));
  loadTextures();
  return true;
}

void		Core::attachObject(Asset3d *obj)
{
  _assets.push_back(obj);
}

void				Core::intro()
{
  Player	*player;
  Gamer		*tmpGame;

  tmpGame = new Gamer;
  _assets[SKYBOX]->setScale(glm::vec3(10.5 * (30) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(15 / 2, 0, 15 / 2));
  for (unsigned int i = 0; i < tmpGame->getRcs()->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(tmpGame->getRcs()->getPlayer(i));
      player->animation = new Animation(_assets[PLAYER]->getAnimationFrame(),
					_assets[PLAYER]->getAnimationSpeed());
    }

  Timer		timer(15000000);
  unsigned int id = 0;
  unsigned int x  = 1;

  player = dynamic_cast<Player *>(tmpGame->getRcs()->getPlayer(0));
  while (tmpGame->update(_clock, _input))
    {
      if (timer.isFinished())
	break;
      if (timer.getElapsedTime() > (x * 3000000) || !player->isAlive())
	{
	  id = (id + 1) % tmpGame->getRcs()->getNbPlayer();
	  player = dynamic_cast<Player *>
	    (tmpGame->getRcs()->getPlayer(id));
	  x += 1;
	}
      tmpGame->updateRandCamera(player);
      _context.updateClock(_clock);
      _context.updateInputs(_input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      tmpGame->draw(_clock, _shader, tmpGame->getCamera(0), _assets, _ObjectToAsset, player);
      _context.flush();
    }
  delete tmpGame;
}

void		Core::startGame(bool twoPlayers, std::string const& p1, std::string const& p2)
{
  Player	*player;
  Gamer		*tmpGame;
  int		x = 20;
  int		y = 20;

  if (twoPlayers)
    tmpGame = new Gamer(x, y, _width / 2, _height, twoPlayers, p1, p2, 8);
  else
    tmpGame = new Gamer(x, y, _width, _height, twoPlayers, p1, p2, 8);
  _assets[SKYBOX]->setScale(glm::vec3(10.5 * (x + y) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(x / 2, 0, y / 2));
  for (unsigned int i = 0; i < tmpGame->getRcs()->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(tmpGame->getRcs()->getPlayer(i));
      player->animation = new Animation(_assets[PLAYER]->getAnimationFrame(),
					_assets[PLAYER]->getAnimationSpeed());
    }
  _prev = _game;
  _change = true;
  _game = tmpGame;
}

void		Core::gameMenu()
{
  MenuGrid*	grid = new MenuGrid;
  Text2d*	text1 = new Text2d("Width: ", 80, 50, 500, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text2 = new Text2d("Height: ", 80, 125, 500, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text3 = new Text2d("25", 525, 50, 700, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text4 = new Text2d("25", 525, 125, 700, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	start = new Text2d("Start Game", 700, 700, 500, 100, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	aiLabel = new Text2d("Number of AI: ", 80, 200, 500, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	aiField = new Text2d("", 600, 200, 200, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	p1Label = new Text2d("Player1", 80, 275, 300, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	p2Label = new Text2d("Player2", 950, 275, 300, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	p1Field = new Text2d("", 400, 275, 400, 50, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	p2Field = new Text2d("", 1300, 275, 400, 50, "resources/assets/textures/alpha3Blue.tga");

  text4->setModifiable();
  text3->setModifiable();
  aiField->setModifiable();
  p1Field->setModifiable();
  p2Field->setModifiable();
  text4->hideFocus();
  text3->hideFocus();
  aiField->hideFocus();
  p1Field->hideFocus();
  p2Field->hideFocus();
  text2->unFocus();
  text1->unFocus();
  p1Label->unFocus();
  p2Label->unFocus();
  aiLabel->unFocus();
  text3->setDynamic();
  text4->setDynamic();
  grid->addObject(text1, [] (void) {
    ;
  });
  grid->addObject(text2, [] (void) {
    ;
  });
  grid->addObject(aiLabel, [] (void) {
    ;
  });
  grid->addObject(p1Label, [] (void) {
    ;
  });
  grid->addObject(p2Label, [] (void) {
    ;
  });
  grid->addDynObject(text3, [] (void) {
  },
  [text3] (void) {
    int			value;

    value = Conversion::stringToType<int>(text3->getText()) - 1;
    std::cout << value << std::endl;
    text3->setText(Conversion::typeToString(value));
  },
  [text3] (void) {
    int			value;

    value = Conversion::stringToType<int>(text3->getText()) + 1;
    std::cout << value << std::endl;
    text3->setText(Conversion::typeToString(value));
  });
  grid->addDynObject(text4, [] (void) {
  },
  [text4] (void) {
    int			value;

    value = Conversion::stringToType<int>(text4->getText()) - 1;
    std::cout << value << std::endl;
    text4->setText(Conversion::typeToString(value));
  },
  [text4] (void) {
    int			value;

    value = Conversion::stringToType<int>(text4->getText()) + 1;
    std::cout << value << std::endl;
    text4->setText(Conversion::typeToString(value));
  });
  grid->addObject(aiField, [aiField] (void) {
    std::cout << aiField->getText() << std::endl;;
  });
  grid->addObject(p1Field, [p1Field] (void) {
    std::cout << p1Field->getText() << std::endl;;
  });
  grid->addObject(p2Field, [p2Field] (void) {
    std::cout << p2Field->getText() << std::endl;;
  });
  grid->addObject(start, [this, p1Field, p2Field] (void) {
    /// START GAME
    startGame(true, p1Field->getText(), p2Field->getText());
  });
  _prev = _game;
  _change = true;
  _game = grid;
}

void		Core::firstMenu()
{
  MenuGrid*	grid = new MenuGrid;
  View2d*	back = new View2d(0, 0, 1800, 1000, "resources/assets/textures/background.tga");
  View2d*	text1 = new View2d(1100, 325, 500, 101, "resources/assets/textures/load.tga");
  View2d*	text2 = new View2d(1100, 475, 500, 101, "resources/assets/textures/new.tga");
  View2d*	text3 = new View2d(1100, 625, 500, 101, "resources/assets/textures/high.tga");
  View2d*	text4 = new View2d(1100, 775, 500, 101, "resources/assets/textures/quit.tga");

  back->unFocus();
   grid->addObject(back, [] (void) {
    ;
  });
  grid->addObject(text1, [] (void) {
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
  });
  grid->addObject(text2, [this, &grid] (void) {
    this->gameMenu();
  });
  grid->addObject(text3, [] (void) {
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
  });
  grid->addObject(text4, [this] (void) {
    this->_status = true;
  });
  _game = grid;
}

bool		Core::update()
{
  bool ret;

  ret = _game->update(_clock, _input);
  if (_change)
    {
      _change = false;
      delete _prev;
    }
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  if (!ret)
    _status = true;
  return ret;
}

void		Core::draw()
{
  _game->drawAll(_clock, _shader, _assets, _ObjectToAsset);
  _context.flush();
}


gdl::SdlContext		&Core::getContext()
{
  return _context;
}

gdl::Clock		&Core::getClock()
{
  return _clock;
}

gdl::BasicShader	&Core::getShader()
{
  return _shader;
}

bool			Core::isOver() const
{
  return _status;
}

}
