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

class IBomb;

class RessourceStock
{
public:
  enum SoundType { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE,
		   FIRSTBLOOD, SUICIDE, EXPLOSE, PICKUP, HITSHIELD,
		   PREPARE1, PREPARE2, PREPARE3, PREPARE4 };

  static unsigned int const	nbSounds;
  static unsigned int const	nbChannels;

  RessourceStock(std::vector<std::string> const &, unsigned int, ScoreList*, bool, bool intro = false);
  RessourceStock(std::vector<Bomberman::Player*> const& players);
  virtual ~RessourceStock();
  RessourceStock(const RessourceStock &);
  RessourceStock &operator=(const RessourceStock &);

  void		init();
  void		initSounds();

public:
  IObject	*getObject(IObject::Type) const;
  IBuff		*getBuff(IBuff::Type) const;
  IBomb		*getBomb(Bomb::Type) const;
  SoundManager	*getMusic() const;
  SoundManager	*getSound(SoundType);
  Player	*getPlayer(std::string const &) const;
  Player	*getPlayer(unsigned int) const;
  unsigned int	getNbPlayer() const;

public:
  unsigned int	countAlivePlayers();
  bool		isPlayerOneAlive() const;
  bool		isPlayerTwoAlive() const;
  bool		isPlayingMusic() const;
  bool		isPlayingSounds() const;
  void		initMusic();
  void		deleteMusic();
  void		toggleMusic();
  void		toggleSounds();
  Player*	getPlayerOne() const;
  Player*	getPlayerTwo() const;
  Player*	getWinner() const;

private:
  std::vector<Player *>		_players;
  std::vector<IBuff *>		_buffs;
  std::vector<IBomb *>		_bombs;
  std::vector<IObject *>	_objects;
  Player*			_winner;
  AudioManager			_audioManager;
  SoundManager*			_music;
  SoundManager*			_calm;
  std::vector<std::string>	_sounds;
  std::vector<float>		_soundsTime;
  std::vector<std::pair<SoundManager*, Timer*> >	_soundsPlaying;
  bool				_toggleMusic;
  bool				_toggleSounds;
  bool				_twoPlayers;
};

}

#endif /* !RESSOURCESTOCK_H_ */
