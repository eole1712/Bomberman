#include <string>
#include "RessourceStock.hpp"
#include "BuffDecSpeed.hpp"
#include "BuffFactory.hpp"
#include "BuffIncBomb.hpp"
#include "BuffIncRange.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffNoBomb.hpp"
#include "BuffParalyzed.hpp"
#include "BuffShield.hpp"
#include "Empty.hpp"
#include "IBomb.hpp"
#include "BombClassic.hpp"
#include "BombTimer.hpp"
#include "Spawn.hpp"
#include "Wall.hpp"
#include "DestroyableWall.hpp"
#include "Color.hpp"
#include "BombVirus.hpp"
#include "BuffWeapon.hpp"
#include "BombMine.hpp"
#include "Score.hpp"
#include "BombBarrel.hpp"
#include "Sound.hpp"
#include "my_random.hpp"

namespace Bomberman
{

unsigned int const	RessourceStock::nbSounds = 15;

RessourceStock::RessourceStock()
{}

RessourceStock::RessourceStock(std::vector<std::string> const &names, ScoreList* scoreList)
  : _players(names.size(), NULL), _buffs(IBuff::nbBuff, NULL), _bombs(Bomb::nbBomb, NULL), _objects(IObject::nbObject, NULL), _soundManager(10), _sounds(RessourceStock::nbSounds, "")
{
  for (unsigned int i = 0; i < names.size(); ++i)
    {
      _players[i] = new Player(names[i], Color::HSVtoRGB(1.0 / names.size() * i, 1, 1));
      reinterpret_cast<Player*>(_players[i])->linkScoreList(scoreList);
    }
  _buffs[IBuff::INC_SPEED] = new Buff::IncSpeed;
  _buffs[IBuff::DEC_SPEED] = new Buff::DecSpeed;
  _buffs[IBuff::INC_BOMB] = new Buff::IncBomb;
  _buffs[IBuff::INC_RANGE] = new Buff::IncRange;
  _buffs[IBuff::NO_BOMB] = new Buff::NoBomb;
  _buffs[IBuff::PARALYZED] = new Buff::Paralyzed;
  _buffs[IBuff::SHIELD] = new Buff::Shield;
  _buffs[IBuff::WEAPON] = new Buff::Weapon;
  _bombs[Bomb::CLASSIC] = new Bomb::Classic;
  _bombs[Bomb::VIRUS] = new Bomb::Virus;
  _bombs[Bomb::MINE] = new Bomb::Mine;
  _bombs[Bomb::BARREL] = new Bomb::Barrel;
  _objects[IObject::BOMB] = NULL;
  _objects[IObject::BARREL] = NULL;
  _objects[IObject::MINE] = NULL;
  _objects[IObject::VIRUS] = NULL;
  _objects[IObject::PLAYER] = NULL;
  _objects[IObject::BONUS] = NULL;
  _objects[IObject::WALL] = new Wall;
  _objects[IObject::DESTROYABLEWALL] = new DestroyableWall;
  _objects[IObject::SPAWN] = new Spawn;
  _objects[IObject::EMPTY] = new Empty;
  _objects[IObject::FIRE] = NULL;
  _sounds[TWO] = "./resources/sound/killstreak/rampage.wav";
  _sounds[THREE] = "./resources/sound/killstreak/killingspree.wav";
  _sounds[FOUR] = "./resources/sound/killstreak/dominating.wav";
  _sounds[FIVE] = "./resources/sound/killstreak/unstoppable.wav";
  _sounds[SIX] = "./resources/sound/killstreak/megakill.wav";
  _sounds[SEVEN] = "./resources/sound/killstreak/ultrakill.wav";
  _sounds[EIGHT] = "./resources/sound/killstreak/ludicrouskill.wav";
  _sounds[NINE] = "./resources/sound/killstreak/wickedsick.wav";
  _sounds[TEN] = "./resources/sound/killstreak/monsterkill.wav";
  _sounds[ELEVEN] = "./resources/sound/killstreak/holyshit.wav";
  _sounds[TWELVE] = "./resources/sound/killstreak/godlike.wav";
  _sounds[FIRSTBLOOD] = "./resources/sound/firstblood.wav";
  _sounds[MINE] = "./resources/sound/mine.wav";
}

RessourceStock::RessourceStock(std::vector<Bomberman::Player*> const& players)
  : _players(players.size(), NULL), _buffs(IBuff::nbBuff, NULL), _bombs(Bomb::nbBomb, NULL), _objects(IObject::nbObject, NULL), _soundManager(10), _sounds(RessourceStock::nbSounds, "")
{
  for (unsigned int i = 0; i < players.size(); ++i)
    _players[i] = players[i];
  _buffs[IBuff::INC_SPEED] = new Buff::IncSpeed;
  _buffs[IBuff::DEC_SPEED] = new Buff::DecSpeed;
  _buffs[IBuff::INC_BOMB] = new Buff::IncBomb;
  _buffs[IBuff::INC_RANGE] = new Buff::IncRange;
  _buffs[IBuff::NO_BOMB] = new Buff::NoBomb;
  _buffs[IBuff::PARALYZED] = new Buff::Paralyzed;
  _buffs[IBuff::SHIELD] = new Buff::Shield;
  _buffs[IBuff::WEAPON] = new Buff::Weapon;
  _bombs[Bomb::CLASSIC] = new Bomb::Classic;
  _bombs[Bomb::VIRUS] = new Bomb::Virus;
  _bombs[Bomb::MINE] = new Bomb::Mine;
  _bombs[Bomb::BARREL] = new Bomb::Barrel;
  _objects[IObject::BOMB] = NULL;
  _objects[IObject::BARREL] = NULL;
  _objects[IObject::MINE] = NULL;
  _objects[IObject::VIRUS] = NULL;
  _objects[IObject::PLAYER] = NULL;
  _objects[IObject::BONUS] = NULL;
  _objects[IObject::WALL] = new Wall;
  _objects[IObject::DESTROYABLEWALL] = new DestroyableWall;
  _objects[IObject::SPAWN] = new Spawn;
  _objects[IObject::EMPTY] = new Empty;
  _objects[IObject::FIRE] = NULL;
  _sounds[TWO] = "./resources/sound/killstreak/rampage.wav";
  _sounds[THREE] = "./resources/sound/killstreak/killingspree.wav";
  _sounds[FOUR] = "./resources/sound/killstreak/dominating.wav";
  _sounds[FIVE] = "./resources/sound/killstreak/unstoppable.wav";
  _sounds[SIX] = "./resources/sound/killstreak/megakill.wav";
  _sounds[SEVEN] = "./resources/sound/killstreak/ultrakill.wav";
  _sounds[EIGHT] = "./resources/sound/killstreak/ludicrouskill.wav";
  _sounds[NINE] = "./resources/sound/killstreak/wickedsick.wav";
  _sounds[TEN] = "./resources/sound/killstreak/monsterkill.wav";
  _sounds[ELEVEN] = "./resources/sound/killstreak/holyshit.wav";
  _sounds[TWELVE] = "./resources/sound/killstreak/godlike.wav";
  _sounds[FIRSTBLOOD] = "./resources/sound/firstblood.wav";
  _sounds[MINE] = "./resources/sound/mine.wav";
}

RessourceStock::~RessourceStock()
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      delete _players[i];
    }
  for (unsigned int i = 0; i < _buffs.size(); ++i)
    {
      delete _buffs[i];
    }
  for (unsigned int i = 0; i < _objects.size(); ++i)
    {
      delete _objects[i];
    }
}

IObject		*RessourceStock::getObject(IObject::Type type) const
{
  return _objects[type];
}

IObject		*RessourceStock::getBuff(IBuff::Type type) const
{
  return _buffs[type];
}

IObject		*RessourceStock::getBomb(Bomb::Type type) const
{
  return _bombs[type];
}

SoundManager*		RessourceStock::getSound(SoundType type)
{
  if (type == PREPARE)
    return (new SoundManager("./resources/sound/prepare"
			     + Conversion::typeToString<unsigned int>(my_random(1, 4)) + ".wav"));
  else if (type == SUICIDE)
    return (new SoundManager("./resources/sound/suicide"
			     + Conversion::typeToString<unsigned int>(my_random(1, 5)) + ".wav"));
  else
    return (new SoundManager(_sounds[type]));
}

IObject		*RessourceStock::getPlayer(std::string const &name) const
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      if ((dynamic_cast<Player *>(_players[i])->getName()) == name)
	  return _players[i];
    }
  return NULL; //EXCEPTION???
}

IObject		*RessourceStock::getPlayer(unsigned int id) const
{
  if (id >= _players.size())
    return NULL; //EXCEPTION???
  return _players[id];
}

unsigned int	RessourceStock::getNbPlayer() const
{
  return _players.size();
}

}
