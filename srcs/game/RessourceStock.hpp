#ifndef RESSOURCESTOCK_H_
# define RESSOURCESTOCK_H_

# include <vector>
# include <string>
# include "IObject.hpp"
# include "IBuff.hpp"
# include "IBomb.hpp"
# include "Player.hpp"
# include "ScoreList.hpp"
# include "Sound.hpp"
# include "RessourceStock.hpp"

namespace Bomberman
{

class RessourceStock
{
public:
  enum SoundType { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE,
		   FIRSTBLOOD, SUICIDE, EXPLOSE, PREPARE1, PREPARE2, PREPARE3, PREPARE4 };

  static unsigned int const	nbSounds;
  static unsigned int const	nbChannels;

  RessourceStock(std::vector<std::string> const &, unsigned int, ScoreList*);
  RessourceStock(std::vector<Bomberman::Player*> const& players);
  virtual ~RessourceStock();
  RessourceStock(const RessourceStock &);
  RessourceStock &operator=(const RessourceStock &);

  void		init();

public:
  IObject	*getObject(IObject::Type) const;
  IObject	*getBuff(IBuff::Type) const;
  IObject	*getBomb(Bomb::Type) const;
  SoundManager	*getMusic() const;
  SoundManager	*getSound(SoundType);
  IObject	*getPlayer(std::string const &) const;
  IObject	*getPlayer(unsigned int) const;
  unsigned int	getNbPlayer() const;

  bool		isPlayingMusic() const;
  bool		isPlayingSounds() const;
  void		initMusic();
  void		deleteMusic();
  void		toggleMusic();
  void		toggleSounds();

private:
  std::vector<IObject *>	_players;
  std::vector<IObject *>	_buffs;
  std::vector<IObject *>	_bombs;
  std::vector<IObject *>	_objects;
  AudioManager			_audioManager;
  SoundManager*			_music;
  SoundManager*			_calm;
  std::vector<std::string>	_sounds;
  std::vector<SoundManager*>	_soundsPlaying;
  bool				_toggleMusic;
  bool				_toggleSounds;
};

}

#endif /* !RESSOURCESTOCK_H_ */
