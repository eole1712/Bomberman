#include <iostream>
#include "JSONDoc.hpp"
#include "Score.hpp"

int	main()
{
  Bomberman::Score score;
  JSONDoc doc;

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
  doc.serialize<Bomberman::Score>(score);
  doc.writeDown("Test1.json");
  Bomberman::Score score2 = doc.unserialize<Bomberman::Score>();
  if (score == score2)
    std::cout << "Fuck Yeah" << std::endl;
  else
    throw std::runtime_error("Ya une couille dans le pâté");
  //std::cout << score2.getScore("Bomby").front() << std::endl;
}
