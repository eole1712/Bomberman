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
  init();
}

Core::Core(const unsigned int & width, const unsigned int & height)
  : _change(false), _width(width), _height(height)
{
  init();
}

Core::~Core()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
    delete (*i);
  _json->serialize<Bomberman::MapList>(*_mapList);
  _json->serialize<Bomberman::ScoreList>(*_scoreList);
  _json->writeDown("./resources/json/Gamedata.json");
  delete (_mapList);
  delete (_scoreList);
  delete _game;
  delete _json;
}

void	Core::init()
{
  _status = false;
  _json = new JSONDoc;
  _mapList = ((_json->parse("./resources/json/Gamedata.json"))
	      ? (_json->unserialize<Bomberman::MapList*>())
	      : (new MapList()));
  _scoreList = ((_json->parse("./resources/json/Gamedata.json"))
		? (_json->unserialize<Bomberman::ScoreList*>())
		: (new ScoreList()));
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
  _assets[BOMB]->translate(glm::vec3(-0.5, -0.5, 0));
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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (!_shader.load("resources/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("resources/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;
  _shader.bind();
  _shader.setUniform("color", glm::vec4(1.0));
  _shader.setUniform("aplha", glm::vec4(0));
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
  View2d*	intro = new View2d(0, 0, 741, 300, "resources/assets/textures/intro_1.tga");
  View2d*	intro2 = new View2d(580, 670, 639, 130, "resources/assets/textures/intro_2.tga");
  Timer		timer(30000000);
  unsigned int	x = 1;

  tmpGame = new Gamer(NULL, NULL);
  _assets[SKYBOX]->setScale(glm::vec3(10.5 * (30) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(15 / 2, 0, 15 / 2));
  for (unsigned int i = 0; i < tmpGame->getRcs()->getNbPlayer(); ++i)
    {
      player = tmpGame->getRcs()->getPlayer(i);
      player->setAnimation(new Animation(_assets[PLAYER]->getAnimationFrame(),
					 _assets[PLAYER]->getAnimationSpeed()));
    }
  while (tmpGame->update(_clock, _input))
    {
      if (timer.isFinished())
	break;
      tmpGame->updateRandCamera();
      _context.updateClock(_clock);
      _context.updateInputs(_input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      tmpGame->draw(_clock, _shader, tmpGame->getCamera(0), _assets, _ObjectToAsset, NULL);
      _shader.setUniform("view", glm::mat4());
      _shader.setUniform("projection", glm::ortho(0.0f, 1800.0f, 900.0f, 0.0f, -1000.0f, 1000.0f));
      intro->draw(_shader);

      if (timer.getElapsedTime() > 400000 * x)
	{
	  intro2->setHidden(!intro2->isHidden());
	  x += 1;
	}
      intro2->draw(_shader);
      _context.flush();
    }
  delete intro;
  _game = tmpGame;
}

void		Core::startGame(bool twoPlayers, std::string const& p1, std::string const& p2,
				unsigned int x, unsigned int y, unsigned int nbAI, std::string mapName)
{
  Player	*player;
  Gamer		*tmpGame;

  if (twoPlayers)
    tmpGame = new Gamer(x, y, _width / 2, _height, twoPlayers, p1, p2, nbAI + 2, _mapList->getMap(mapName), _scoreList);
  else
    tmpGame = new Gamer(x, y, _width, _height, twoPlayers, p1, p2, nbAI + 1, _mapList->getMap(mapName), _scoreList);
  _assets[SKYBOX]->setScale(glm::vec3(10.5 * (x + y) / 2));
  _assets[SKYBOX]->setPosition(glm::vec3(x / 2, 0, y / 2));
  for (unsigned int i = 0; i < tmpGame->getRcs()->getNbPlayer(); ++i)
    {
      player = tmpGame->getRcs()->getPlayer(i);
      player->setAnimation(new Animation(_assets[PLAYER]->getAnimationFrame(),
					 _assets[PLAYER]->getAnimationSpeed()));
    }
  _prev = _game;
  _change = true;
  _game = tmpGame;
}

void		Core::gameMenu()
{
  MenuGrid*	grid = new MenuGrid;
  View2d*	background = new View2d(0, 0, 1800, 900, "resources/assets/textures/menu_2_background.tga");
  Text2d*	map_height = new Text2d("20", 1475, 360, 100, 50, "resources/assets/textures/police.tga");
  Text2d*	map_width = new Text2d("20", 1475, 300, 100, 50, "resources/assets/textures/police.tga");
  Text2d*	aiField = new Text2d("10", 1475, 420, 100, 50, "resources/assets/textures/police.tga");
  Text2d*	pField = new Text2d("1", 1485, 480, 100, 50, "resources/assets/textures/police.tga");
  Text2d*	p1Field = new Text2d("Player1", 1115, 600, 400, 50, "resources/assets/textures/police.tga");
  Text2d*	p2Field = new Text2d("Player2", 1115, 660, 400, 50, "resources/assets/textures/police.tga");
  View2d*	start = new View2d(1065, 720, 350, 50, "resources/assets/textures/menu_2_start.tga");
  View2d*	p1TextBackGround = new View2d(1110, 600, 410, 55, "resources/assets/textures/menu_2_placeholder.tga");
  View2d*	p2TextBackGround = new View2d(1110, 660, 410, 55, "resources/assets/textures/menu_2_placeholder.tga");
  View2d*	back = new View2d(1500, 820, 250, 60, "resources/assets/textures/menu_2_back.tga");

  p1Field->setModifiable();
  p2Field->setModifiable();
  p2Field->unFocus();
  p2Field->setHidden(true);
  p2TextBackGround->unFocus();
  p2TextBackGround->setHidden(true);
  p1TextBackGround->unFocus();
  aiField->setDynamic();
  pField->setDynamic();
  map_height->setDynamic();
  map_width->setDynamic();
  background->unFocus();
  grid->addObject(background, [] (void) {
    ;
  });
  grid->addObject(p1TextBackGround, [] (void) {
    ;
  });
  grid->addObject(p2TextBackGround, [] (void) {
    ;
  });
  grid->addDynObject(map_width, [] (void) {
  },
  [aiField, map_width, map_height, pField] (void) {
    int			value;
    int			mapY;
    int			nbPlayer;
    int			nbAI;

    nbAI = Conversion::stringToType<int>(aiField->getText());
    nbPlayer = Conversion::stringToType<int>(pField->getText());
    mapY = Conversion::stringToType<int>(map_height->getText());

    value = Conversion::stringToType<int>(map_width->getText()) - 1;
    if (value <= 10)
      value = 10;

    if (nbAI + nbPlayer >= (mapY * value / 16))
      nbAI = (mapY * value / 16) - nbPlayer;
    aiField->setText(Conversion::typeToString(nbAI));
    map_width->setText(Conversion::typeToString(value));
  },
  [map_width] (void) {
    int			value;

    value = Conversion::stringToType<int>(map_width->getText()) + 1;
    map_width->setText(Conversion::typeToString(value));
  });
  grid->addDynObject(map_height, [] (void) {
  },
  [aiField, map_width, map_height, pField] (void) {
    int			value;
    int			mapX;
    int			nbPlayer;
    int			nbAI;

    nbAI = Conversion::stringToType<int>(aiField->getText());
    nbPlayer = Conversion::stringToType<int>(pField->getText());
    mapX = Conversion::stringToType<int>(map_width->getText());
    value = Conversion::stringToType<int>(map_height->getText()) - 1;

    if (value <= 10)
      value = 10;

    if (nbAI + nbPlayer >= (mapX * value / 16))
      nbAI = (mapX * value / 16) - nbPlayer;
    aiField->setText(Conversion::typeToString(nbAI));

    map_height->setText(Conversion::typeToString(value));
  },
  [map_height] (void) {
    int			value;

    value = Conversion::stringToType<int>(map_height->getText()) + 1;

    map_height->setText(Conversion::typeToString(value));
  });

  grid->addDynObject(aiField, [aiField] (void) {
  },
  [aiField, pField] (void) {
    int			value;
    int			nbPlayer;

    value = Conversion::stringToType<int>(aiField->getText()) - 1;
    nbPlayer = Conversion::stringToType<int>(pField->getText());

    if (value <= 0)
      value = 0 + (nbPlayer == 1);

    aiField->setText(Conversion::typeToString(value));

  },
  [aiField, map_width, map_height, pField] (void) {
    int			value;
    int			mapX;
    int			mapY;
    int			nbPlayer;

    nbPlayer = Conversion::stringToType<int>(pField->getText());
    mapX = Conversion::stringToType<int>(map_width->getText());
    mapY = Conversion::stringToType<int>(map_height->getText());
    value = Conversion::stringToType<int>(aiField->getText()) + 1;
    if (value + nbPlayer >= (mapX * mapY / 16))
      value = (mapX * mapY / 16) - nbPlayer;
    aiField->setText(Conversion::typeToString(value));
  });
  grid->addDynObject(pField, [pField] (void) {
  },
  [pField, p2TextBackGround, p2Field, aiField] (void) {
    int			value;
    int			nbAI;

    nbAI = Conversion::stringToType<int>(aiField->getText());
    value = Conversion::stringToType<int>(pField->getText()) - 1;
    if (value <= 1)
      {
	p2TextBackGround->setHidden(true);
	p2Field->setHidden(true);
	p2Field->unFocus();
	value = 1;
      }
    else
      {
	p2TextBackGround->setHidden(false);
	p2Field->setHidden(false);
	p2Field->reFocus();
	value = 2;
      }
    pField->setText(Conversion::typeToString(value));
    if (nbAI == 0)
      aiField->setText("1");
  },
  [pField, p2TextBackGround, p2Field, aiField, map_width, map_height] (void) {
    int			value;
    int			mapX;
    int			mapY;
    int			nbAI;

    value = Conversion::stringToType<int>(pField->getText()) + 1;
    if (value <= 1)
      {
	p2TextBackGround->setHidden(true);
	p2Field->setHidden(true);
	p2Field->unFocus();
	value = 1;
      }
    else
      {
	p2TextBackGround->setHidden(false);
	p2Field->setHidden(false);
	p2Field->reFocus();
	value = 2;
      }

    nbAI = Conversion::stringToType<int>(aiField->getText());
    mapX = Conversion::stringToType<int>(map_width->getText());
    mapY = Conversion::stringToType<int>(map_height->getText());
    if (value + nbAI > (mapX * mapY / 16))
      nbAI = (mapX * mapY / 16) - value;
    aiField->setText(Conversion::typeToString(nbAI));

    pField->setText(Conversion::typeToString(value));
  });
  grid->addObject(p1Field, [p1Field] (void) {
  });
  grid->addObject(p2Field, [p2Field] (void) {
  });
  grid->addObject(start, [this, p1Field, p2Field, map_height, map_width, aiField, pField] (void) {
    // START GAME

    int height = Conversion::stringToType<int>(map_height->getText());
    int width = Conversion::stringToType<int>(map_width->getText());
    int ai = Conversion::stringToType<int>(aiField->getText());
    bool players = Conversion::stringToType<int>(pField->getText()) == 1 ? false : true;

    startGame(players, p1Field->getText(), p2Field->getText(), height, width, ai, "");
  });
  grid->addObject(back, [this] (void) {
    selectMenu();
  });



  _prev = _game;
  _change = true;
  _game = grid;
}

void		Core::selectMenu()
{
  MenuGrid*	grid = new MenuGrid;
  View2d*	background = new View2d(0, 0, 1800, 900, "resources/assets/textures/menu_select.tga");
  View2d*	map1 = new View2d(195, 200, 330, 136, "resources/assets/textures/menu_select_map1.tga");
  View2d*	map2 = new View2d(200, 300, 330, 136, "resources/assets/textures/menu_select_map2.tga");
  View2d*	map3 = new View2d(200, 400, 330, 136, "resources/assets/textures/menu_select_map3.tga");
  View2d*	custom = new View2d(700, 650, 636, 126, "resources/assets/textures/menu_select_custom.tga");
  View2d*	back = new View2d(1500, 750, 264, 124, "resources/assets/textures/menu_select_back.tga");

  background->unFocus();
  grid->addObject(background, [] (void) {

  });
  grid->addObject(map1, [this] (void) {
    gameMenu();
  });
  grid->addObject(map2, [this] (void) {
    gameMenu();
  });
  grid->addObject(map3, [this] (void) {
    gameMenu();
  });
  grid->addObject(custom, [this] (void) {
    gameMenu();
  });

  grid->addObject(back, [this] (void) {
    firstMenu();
  });

  _prev = _game;
  _change = true;
  _game = grid;
}

unsigned int	Core::lengthCalc(unsigned int nb)
{
  unsigned int	result = 0;

  while (nb > 9)
    {
      ++result;
      nb = nb / 10;
    }
  return (result);
}

void		Core::scoreMenu()
{
  MenuGrid*	grid = new MenuGrid;
  View2d*	background = new View2d(0, 0, 1800, 900, "resources/assets/textures/menu_score.tga");
  View2d*	back = new View2d(458, 768, 619, 106, "resources/assets/textures/menu_score_back.tga");
  std::vector<std::pair<std::string, unsigned int> >	top5 = _scoreList->top(5);
  Text2d*	top[5];

  background->unFocus();
  grid->addObject(background, [] (void) {

  });

  grid->addObject(back, [this] (void) {
    firstMenu();
  });

  for (unsigned int i = 0 ; i < 5 ; ++i)
    {
      if (top5[i].first != "")
	{
	  top[i] = new Text2d((top5[i].first + std::string(14 - top5[i].first.size() - lengthCalc(top5[i].second), ' ')
			       + Conversion::typeToString<unsigned int>(top5[i].second)),
			      410, 280 + (i * ((i < 3) ? (110) : (102))), 1200, 55,
			      "resources/assets/textures/police.tga");
	  top[i]->unFocus();
	  grid->addObject(top[i], [] (void) {});
	}
    }

  _prev = _game;
  _change = true;
  _game = grid;
}

void		Core::firstMenu()
{
  MenuGrid*	grid = new MenuGrid;
  View2d*	back = new View2d(0, 0, 1800, 900, "resources/assets/textures/background.tga");
  View2d*	text1 = new View2d(1100, 475, 500, 101, "resources/assets/textures/load.tga");
  View2d*	text2 = new View2d(1100, 325, 500, 101, "resources/assets/textures/new.tga");
  View2d*	text3 = new View2d(1100, 625, 500, 101, "resources/assets/textures/high.tga");
  View2d*	text4 = new View2d(1100, 775, 500, 101, "resources/assets/textures/quit.tga");

  back->unFocus();
   grid->addObject(back, [] (void) {
    ;
  });
  grid->addObject(text2, [this, &grid] (void) {
    this->selectMenu();
  });
  grid->addObject(text1, [this] (void) {
    Gamer *tmpGame = NULL;
    Player* player;
    JSONDoc j;
    if (j.parse("resources/SavedDatas.json"))
      {
	std::cout << "Ca marche" << std::endl;
	tmpGame = j.unserialize<Bomberman::Gamer*>("");
    for (unsigned int i = 0; i < tmpGame->getRcs()->getNbPlayer(); ++i)
      {
	player = tmpGame->getRcs()->getPlayer(i);
	player->setAnimation(new Animation(_assets[PLAYER]->getAnimationFrame(),
					_assets[PLAYER]->getAnimationSpeed()));
      }
    _prev = _game;
    _change = true;
    _game = tmpGame;
      }
    std::cout << "Désolé, fonctionnalité encore non implémentée" << std::endl;
  });
  grid->addObject(text3, [this] (void) {
    scoreMenu();
  });
  grid->addObject(text4, [this] (void) {
    this->_status = true;
  });
  _prev = _game;
  _change = true;
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

bool			Core::isOver() const
{
  return _status;
}

}
