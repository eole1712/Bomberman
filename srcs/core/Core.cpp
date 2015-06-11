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
#include "Core.hpp"

namespace Bomberman
{

Core::Core()
  : _change(false), _width(1800), _height(900)
{
}

Core::Core(const unsigned int & width, const unsigned int & height)
  : _change(false), _width(width), _height(height)
{
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
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
  // _assets[SKYBOX]->scale(glm::vec3(10.5 * (_height + _width) / 2));
  // _assets[SKYBOX]->setPosition(glm::vec3(_width / 2, 0, _height / 2));
  _assets[SKYBOX]->scale(glm::vec3(5 * (30 + 30) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(30 / 2, 0, 30 / 2));
  _assets[BONUS]->scale(glm::vec3(0.05));

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
  loadTextures();
  _shader.bind();
  return true;
}

void		Core::attachObject(Asset3d *obj)
{
  _assets.push_back(obj);
}

void		Core::startGame()
{
  Player	*player;
  Gamer		*tmpGame;

  tmpGame = new Gamer(15, 15, _width / 2, _height);
  for (unsigned int i = 0; i < tmpGame->_stock->getNbPlayer(); ++i)
    {
      player = dynamic_cast<Player *>(tmpGame->_stock->getPlayer(i));
      player->animation = new Animation(_assets[PLAYER]->getAnimationFrame(),
					_assets[PLAYER]->getAnimationSpeed());
    }
  _prev = _game;
  _change = true;
  _game = tmpGame;
}

void		Core::gameMenu()
{
  MenuGrid*	gridou = new MenuGrid;
  Text2d*	text1 = new Text2d("Width", 80, 200, 100, 100, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text2 = new Text2d("Height", 80, 300, 100, 100, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text3 = new Text2d("", 200, 200, 200, 100, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text4 = new Text2d("", 200, 300, 200, 100, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	start = new Text2d("Start Game", 200, 600, 500, 150, "resources/assets/textures/alpha3Blue.tga");

  text4->setModifiable();
  text3->setModifiable();
  text2->unFocus();
  text1->unFocus();
  gridou->addObject(text1, [] (void) {
    ;
  });
  gridou->addObject(text2, [] (void) {
    ;
  });
  gridou->addObject(text3, [text3] (void) {
    std::cout << text3->getText() << std::endl;
  });
  gridou->addObject(text4, [text4] (void) {
    std::cout << text4->getText() << std::endl;
  });
  gridou->addObject(start, [this] (void) {
    startGame();
  });
  _prev = _game;
  _change = true;
  _game = gridou;
}

void		Core::firstMenu()
{
  MenuGrid*	grid = new MenuGrid;
  Text2d*	text1 = new Text2d("Load Game", 200, 200, 500, 150, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text2 = new Text2d("Start Game", 200, 350, 500, 150, "resources/assets/textures/alpha3Blue.tga");
  Text2d*	text3 = new Text2d("High Scores", 200, 500, 500, 150, "resources/assets/textures/alpha3Blue.tga");

  grid->addObject(text1, [] (void) {
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
  });
  grid->addObject(text2, [this, &grid] (void) {
    this->gameMenu();
  });
  grid->addObject(text3, [] (void) {
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
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

}
