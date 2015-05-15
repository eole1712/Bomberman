#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Score.hpp"

namespace Bomberman
{

Score::Score()
{
  ;
}

Score::~Score()
{
  ;
}

int	Score::getBestScore(const std::string &name) const
{
  std::unordered_map<int, int> _map;
  std::list<unsigned int> list = _scores.at(name);
  unsigned int tmp = 0;

  std::for_each(list.begin(), list.end(), [&] (unsigned int val) {
    if (val > tmp)
      tmp = val;
  });
  return tmp;
}

std::list<unsigned int> const& Score::getScore(const std::string &name) const
{
  return _scores.at(name);
}

void Score::addScore(const std::string &name, unsigned int score)
{
  _scores[name].push_back(score);
}

std::list<std::string> const Score::getNames() const
{
  std::list<std::string> list;

  std::for_each(_scores.cbegin(), _scores.cend(), [&] (std::pair<std::string, std::list<unsigned int> > pair) {
    list.push_back(pair.first);
  });
  return list;
}

bool Score::operator==(Score const& other) const
{
  return _scores == other._scores;
}

}
