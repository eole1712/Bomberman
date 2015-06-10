#include <iostream>
#include "BuffNoBomb.hpp"
#include "BuffShield.hpp"
#include "BuffIncRange.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffFactory.hpp"
#include "JSONDoc.hpp"
#include "Score.hpp"
#include "Player.hpp"
#include "Map.hpp"


int	main()
{
  Bomberman::Score score;
  JSONDoc doc;
  Bomberman::Player player("Grisha", glm::vec4(0.5, 0, 0.2, 0));
  Bomberman::Player griGri("Putin", glm::vec4(0, 1, 0, 0));
  SmartFactory<Bomberman::IBuff>* fac = Bomberman::Buff::Factory::getInstance();
  std::vector<std::string> players;
  players.push_back("GriGri");
  players.push_back("Putin");
  players.push_back("John");
  players.push_back("Jean");
  players.push_back("Milow");
  Bomberman::Map map("testMap", 10, 10, 5, Bomberman::Map::EASY, new Bomberman::RessourceStock(players));
  player.initGame(&map);
  griGri.initGame(&map);
  fac->learn(new Bomberman::Buff::NoBomb);
  fac->learn(new Bomberman::Buff::Shield);
  fac->learn(new Bomberman::Buff::IncSpeed);
  fac->learn(new Bomberman::Buff::IncRange);
  score.addScore("Arthur", 42);
  score.addScore("Arthur", 420);
  score.addScore("Arthur", 4200);
  score.addScore("Arthur", 42000);

  score.addScore("Bomby", 16);
  score.addScore("Bomby", 32);
  score.addScore("Bomby", 64);
  score.addScore("Bomby", 128000);

  score.addScore("Jona", 22);
  score.addScore("Jona", 22);
  score.addScore("Jona", 22);
  score.addScore("Jona", 41);
  griGri.addBuff(new Bomberman::Buff::IncRange);
  griGri.addBuff(new Bomberman::Buff::Shield);
  griGri.addBuff(new Bomberman::Buff::IncSpeed);
  griGri.addBuff(new Bomberman::Buff::IncSpeed);
  griGri.addBuff(new Bomberman::Buff::IncSpeed);
  griGri.addBuff(new Bomberman::Buff::IncSpeed);
  player.addBuff(new Bomberman::Buff::NoBomb);
  player.addBuff(new Bomberman::Buff::IncSpeed);
  player.addBuff(new Bomberman::Buff::IncRange);
  doc.serialize<Bomberman::Score>(score);
  doc.serialize<Bomberman::Player>(player);
  doc.writeDown("Test1.json");
  Bomberman::Score score2 = doc.unserialize<Bomberman::Score>();
  if (score == score2)
    std::cout << "Fuck Yeah" << std::endl;
  else
    throw std::runtime_error("Ya une couille dans le pâté");
  std::cout << score2.getScore("Bomby").front() << std::endl;
  Bomberman::Player* player2 = doc.unserialize<Bomberman::Player*>("Grisha");
  if (player.getName() == player2->getName())
    std::cout << "Les deux ont le meme nom" << std::endl;
  if (player.getBuffList().front()->getBuff()->getClassName() ==
      player2->getBuffList().front()->getBuff()->getClassName())
    std::cout << "Les deux ont le même premier membre" << std::endl;
  if (player.getBuffList().size() == player2->getBuffList().size())
    std::cout << "Les deux listes ont la même taille" << std::endl;
  doc.serialize<Bomberman::Player>(griGri);
  doc.serialize<Bomberman::Map>(map);
  doc.writeDown("Test1.json");
  Bomberman::Map* map2 = doc.unserialize<Bomberman::Map*>(map.getName());
  bool diff = false;
  if (map.getWidth() != map2->getWidth() || map.getHeight() != map2->getHeight())
    {
      std::cout << "sizes are differents !" << std::endl;
      abort();
    }
  for (unsigned int i = 0; i != map.getWidth(); ++i)
    {
      for (unsigned int j = 0; j != map.getHeight(); ++j)
	{
	  if (map2->getCellValue(i, j)->getObjectType() != map.getCellValue(i, j)->getObjectType())
	    {
	      std::cout << "difference : " << map2->getCellValue(i, j)->getObjectType() << " and " <<  map.getCellValue(i, j)->getObjectType() << std::endl;
	      diff = true;
	      break;
	    }
	}
    }
  if (!diff)
    std::cout << "Map are the same" << std::endl;
}
