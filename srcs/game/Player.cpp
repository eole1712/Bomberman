#include <string>
#include <list>
#include <cmath>
#include <iostream>
#include "Player.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"
#include "Score.hpp"
#include "ScoreList.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "my_random.hpp"

namespace Bomberman
{

unsigned int const	Player::dftRange = 3;
float const		Player::dftSpeed = 1;
unsigned int const	Player::dftShield = 0;
unsigned int const	Player::dftBomb = 1;
Bomb::Type const	Player::dftBombType = Bomb::CLASSIC;

Player::Player(std::string const &name, glm::vec4 color)
  : IObject(), _name(name), _isAlive(true), _isParalyzed(false), _zeroBomb(false), _isPlaced(false), _range(dftRange), _speed(dftSpeed), _shield(dftShield), _bomb(dftBomb), _putBombStatus(false), _bombType(dftBombType), _color(color), _scoreList(NULL), _animation()
{
  this->init();
}

Player::~Player()
{
  for (std::list<BuffTimer*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    delete *it;
  if (_scoreList != NULL)
    _scoreList->addScore(getName(), getScore().getValue());
}

void	Player::init()
{
  _buffOn[IBuff::INC_SPEED] = &Player::incSpeed;
  _buffOn[IBuff::DEC_SPEED] = &Player::decSpeed;
  _buffOn[IBuff::INC_BOMB] = &Player::incBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::incRange;
  _buffOn[IBuff::NO_BOMB] = &Player::disableAttack;
  _buffOn[IBuff::PARALYZED] = &Player::paralyze;
  _buffOn[IBuff::SHIELD] = &Player::incShield;
  _buffOn[IBuff::WEAPON] = &Player::randWeapon;

  _buffOff[IBuff::INC_SPEED] = &Player::decSpeed;
  _buffOff[IBuff::DEC_SPEED] = &Player::incSpeed;
  _buffOff[IBuff::INC_BOMB] = &Player::decBomb;
  _buffOff[IBuff::INC_RANGE] = &Player::decRange;
  _buffOff[IBuff::NO_BOMB] = &Player::enableAttack;
  _buffOff[IBuff::PARALYZED] = &Player::unparalyze;
  _buffOff[IBuff::SHIELD] = &Player::decShield;
  _buffOff[IBuff::WEAPON] = &Player::randWeapon;
}

// getters

std::string const&	Player::getName() const
{
  return _name;
}

unsigned int   		Player::getRange() const
{
  return _range;
}

float   		Player::getSpeed() const
{
  return _speed;
}

bool			Player::isPlayerOne() const
{
  return (_map->getRcs()->getPlayer(0) == this);
}

bool			Player::isPlayerTwo() const
{
  return (_map->getRcs()->getPlayer(_map->getRcs()->getNbPlayer() - 1) == this);
}

bool			Player::isIA() const
{
  return false;
}

// check status

bool			Player::isAlive() const
{
  return _isAlive;
}

bool			Player::isParalyzed() const
{
  return _isParalyzed;
}

bool			Player::isPlaced() const
{
  return _isPlaced;
}

bool			Player::zeroBomb() const
{
  return _zeroBomb || (_bomb == 0);
}

bool			Player::canAbsorb() const
{
  return (_shield > 0);
}

// range methods

void			Player::incRange()
{
  _range++;
}

void			Player::decRange()
{
  if (_range > 2)
  _range--;
}

void			Player::resetRange()
{
  _range = dftRange;
}

// speed methods

void			Player::incSpeed()
{
  if (_speed < 1.6)
  _speed += 0.2;
}

void			Player::decSpeed()
{
  if (_speed > 0.6)
    _speed -= 0.2;
}

void			Player::resetSpeed()
{
  _speed = dftSpeed;
}

// shield methods

void			Player::incShield()
{
  _shield++;
}

void			Player::decShield()
{
  if (_shield > 0)
    _shield--;
  _map->getRcs()->getSound(Bomberman::RessourceStock::HITSHIELD)->play();
}

void			Player::resetShield()
{
  _shield = dftShield;
}

// bomb methods

unsigned int		Player::getNbBomb() const
{
  return _bomb;
}

bool			Player::getPutBombStatus() const
{
  return _putBombStatus;
}

unsigned int		Player::getShield() const
{
  return _shield;
}

void			Player::setPutBombStatus(bool status)
{
  _putBombStatus = status;
}


void			Player::incBomb()
{
  _bomb++;
}

void			Player::decBomb()
{
  if (_bomb > 0)
    _bomb--;
}

void			Player::resetBomb()
{
  _bomb = dftBomb;
}

void			Player::enableAttack()
{
  _zeroBomb = false;
}

void			Player::disableAttack()
{
  _zeroBomb = true;
}

// paralyze methods

void			Player::paralyze()
{
  _animation->stop();
  _isParalyzed = true;
}

void			Player::unparalyze()
{
  _animation->start();
  _isParalyzed = false;
}

void			Player::randWeapon()
{
  setBombType((Bomb::Type)(my_random(1, Bomb::nbBomb - 1)));
}

// buff methods
void			Player::addBuff(IBuff *n)
{
  (this->*_buffOn[n->getBuffType()])();
  if (n->getDuration() != IBuff::infinite)
    {
      BuffTimer		*buff = new BuffTimer(n);

      _buff.push_back(buff);
      buff->start();
    }
}

void			Player::addTimedBuff(Bomberman::BuffTimer *buff)
{
  (this->*_buffOn[buff->getBuff()->getBuffType()])();
  _buff.push_back(buff);
  buff->start();
}


void			 Player::checkBuffList()
{
  for (std::list<BuffTimer*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      if ((*it)->isFinished())
	{
	  (this->*_buffOff[(*it)->getBuff()->getBuffType()])();
	  delete (*it);
	  it = _buff.erase(it);
	}
    }
}

std::list<BuffTimer*> const& Player::getBuffList() const
{
  return _buff;
}

// position methods

void			Player::initGame(unsigned int x, unsigned int y, Map *map)
{
  if (map)
    {
      _map = map;
      if (_map->getWidth() > x && _map->getHeight() > y)
	{
	  setPosition(glm::vec3(x, 0, y));
	}
    }
}

void			Player::initGame(Map *map)
{
  if (map)
    {
      _map = map;
      Map::TwoInt	two = map->findEmptySpawn();

      if (_map->getWidth() > two.first && _map->getHeight() > two.second)
	{
	  setPosition(glm::vec3(two.first + 0.5, 0, two.second + 0.5));
	  _isPlaced = true;
	}
    }
}

unsigned int		Player::getX() const
{
  return floor(getPosition().x);
}

float			Player::getfX() const
{
  return getPosition().x;
}

unsigned int		Player::getY() const
{
  return floor(getPosition().z);
}

float			Player::getfY() const
{
  return getPosition().z;
}

void			Player::setX(float x)
{
  setPosition(glm::vec3(x, 0, getPosition().z));
}

void			Player::setY(float y)
{
  setPosition(glm::vec3(getPosition().x, 0, y));
}

void			Player::move(const float & direction, float const & elsapsedTime)
{
  glm::vec3		pos;
  glm::vec3		npos;
  IObject::Type		type;
  float			speedbra;
  unsigned int		animFrame;

  if (!isAlive() || isParalyzed())
    return ;
  speedbra = _speed * elsapsedTime;
  pos = glm::rotate(glm::vec3(0, 0, 0.06), direction, glm::vec3(0, 1, 0)) * speedbra;
  if (pos.x > 1)
    pos.x = 1;
  if (pos.z > 1)
    pos.z = 1;
  if (pos.x < -1)
    pos.x = -1;
  if (pos.z < -1)
    pos.z = -1;
  npos = getPosition() + pos;
  if (npos.x > 0 && npos.x < _map->getWidth())
    {
      type = _map->getCellValue(static_cast<int>(npos.x), static_cast<int>(getPosition().z))->getObjectType();
      if ((type != IObject::DESTROYABLEWALL && type != IObject::WALL && type < IObject::BOMB) ||
	  (static_cast<int>(npos.x) == static_cast<int>(getX()) && static_cast<int>(getPosition().z) == static_cast<int>(getY())))
	translate(glm::vec3(pos.x, 0, 0));
    }
  if (npos.z > 0 && npos.z < _map->getHeight())
    {
      type = _map->getCellValue(static_cast<int>(getPosition().x), static_cast<int>(npos.z))->getObjectType();
      if ((type != IObject::DESTROYABLEWALL && type != IObject::WALL && type < IObject::BOMB) ||
	  (static_cast<int>(getPosition().x) == static_cast<int>(getX()) && static_cast<int>(npos.z) == static_cast<int>(getY())))
	translate(glm::vec3(0, 0, pos.z));
    }

  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::BONUS)
    {
      addBuff(dynamic_cast<IBuff*>(_map->getCellValue(getX(), getY())));
      _map->killObject(getX(), getY());
      _map->getRcs()->getSound(Bomberman::RessourceStock::PICKUP)->play();
    }
  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::FIRE)
    {
      dynamic_cast<Fire*>(_map->getCellValue(getX(), getY()))->getPlayer()->incScore();
      _map->getRcs()->getSound(Bomberman::RessourceStock::SUICIDE)->play();
      tryToKill();
    }
  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::MINE)
    {
      dynamic_cast<BombTimer*>(_map->getCellValue(getX(), getY()))->setFinished(true);
    }
  if (_animation->queueEmpty())
    {
      _animation->setAnim(10, 34, false,
			 _animation->getDefaultSpeed() / (getSpeed() + 0.5));
      _animation->setAnim(34, 55, false, _animation->getDefaultSpeed() / getSpeed(), true);
      _animation->setAnim(55, 119, false,
			 _animation->getDefaultSpeed() / (getSpeed() + 0.5));
    }
  animFrame = _animation->getFrame();
  if (animFrame >= 34 && animFrame < 55)
    _animation->extend();
}

bool			Player::rotate(bool const & direction,
				       float const & elsapsedTime, float const & stop)
{
  float			before;
  float			after;

  before = getRotation().y;
  rotate(direction, elsapsedTime);
  after = getRotation().y;
  after -= 360 * (stop == 0 && direction == 1);
  before -= 360 * (stop == 0 && direction == 1);
  if (abs(stop - before) < abs(stop - after))
    {
      setRotation(glm::vec3(0, stop, 0));
      return true;
    }
  return false;
}

void			Player::rotate(bool const & direction,
				       float const & elsapsedTime)
{
  glm::vec3		rot;

  if (!isAlive() || isParalyzed())
    return;
  rot = getRotation();
  if (direction)
    setRotation(glm::vec3(rot.x, fmod(getRotation().y + 3 * elsapsedTime * _speed, 360), rot.z));
  else
    {
      if (rot.y - 3 * elsapsedTime * _speed < 0)
	setRotation(glm::vec3(rot.x, 360 + rot.y - 3 * elsapsedTime * _speed, rot.z));
      else
	setRotation(glm::vec3(rot.x, rot.y - 3 * elsapsedTime * _speed, rot.z));
    }
}

//attacks

void			Player::setBombType(Bomb::Type type)
{
  _bombType = type;
}

Bomb::Type		Player::getBombType() const
{
  return _bombType;
}

void			Player::putBomb()
{
  if (_map && isAlive() && !isParalyzed() && !zeroBomb() && _map->getCellValue(getX(), getY())->getObjectType() == IObject::EMPTY)
    {
      IBomb	*bomb = _map->getRcs()->getBomb(getBombType());
      BombTimer	*bombT = new BombTimer(this, getRange(), bomb);

      _map->addBomb(bombT);
      _map->setCellValue(getX(), getY(), bombT);
      decBomb();
    }
}

void			Player::putTimedBomb(unsigned int x, unsigned int y)
{
  if (_map && _map->getCellValue(x, y)->getObjectType() == IObject::EMPTY)
    {
      IBomb		*bomb = _map->getRcs()->getBomb(Bomb::CLASSIC);
      BombTimer		*bombT = new BombTimer(this, getRange(), bomb, 0.5, x, y, true);

      _map->addBomb(bombT);
      _map->setCellValue(x, y, bombT);
    }
}

bool			Player::tryToKill()
{
  if (isAlive())
    {
      if (canAbsorb())
	decShield();
      else
	{
	  _isAlive = false;
	  _timeDead = new Timer(5000000);
	  return true;
	}
      return false;
    }
  return false;
}

Timer*			Player::getDeadTimer() const
{
  return _timeDead;
}

// color

void			Player::setColor(glm::vec4 color)
{
  _color = color;
}

glm::vec4 const&	Player::getColor() const
{
  return _color;
}

// score

Score			Player::getScore() const
{
  return _score;
}

void			Player::incScore()
{
  this->_score.inc(this->_map->getRcs());
}

void			Player::linkScoreList(Bomberman::ScoreList* scoreList)
{
  this->_scoreList = scoreList;
}

// type

IObject::Type		Player::getObjectType() const
{
  return IObject::PLAYER;
}

glm::vec3		Player::getNewPos(Player const *sec) const
{
  glm::vec3		t(0, 0, 0);

  t.x = (getPosition().x + sec->getPosition().x) / 2;
  t.y = (getPosition().y + sec->getPosition().y) / 2;
  t.z = (getPosition().z + sec->getPosition().z) / 2;
  return t;
}

glm::vec3		Player::getAbsVec(Player const *sec) const
{
  return (getPosition() - sec->getPosition());
}


bool			Player::isNull() const
{
  return false;
}

Animation*		Player::getAnimation() const
{
  return _animation;
}

void			Player::setAnimation(Animation *animation)
{
  _animation = animation;
}

void			Player::draw(Asset3d & asset, gdl::BasicShader & shader,
				     gdl::Clock const & clock) const
{
  if (isAlive())
    {
      asset.setPosition(this->getPosition() + glm::vec3(-0.5, 0, -0.5));
      asset.setRotation(this->getRotation());
      if (isParalyzed())
	shader.setUniform("alpha", glm::vec4(0.2, 0.76, 1, 0.5));
      else
	shader.setUniform("color", getColor());
      asset.draw(shader, clock, *this->_animation);
      if (isParalyzed())
	shader.setUniform("alpha", glm::vec4(0));
      else
	shader.setUniform("color", glm::vec4(0));
    }
}

int			Player::getId() const
{
  return _id;
}

void			Player::setId(int id)
{
  _id = id;
}

}
