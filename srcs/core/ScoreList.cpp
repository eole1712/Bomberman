#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "ScoreList.hpp"

namespace Bomberman
{

ScoreList::ScoreList()
{
  ;
}

ScoreList::~ScoreList()
{
  ;
}

bool	ScoreList::contains(std::vector<std::pair<std::string, unsigned int> > const& list,
			    std::pair<std::string, unsigned int> const& element) const
{
  unsigned int	count = 0;
  unsigned int	count2 = 0;

  std::for_each(list.begin(), list.end(), [&element, &count] (std::pair<std::string, unsigned int> const& pair) {
    if (pair.first == element.first && pair.second == element.second)
      ++count;
  });

  std::for_each(this->_scores.begin(), this->_scores.end(), [&element, &count2] (std::pair<std::string, std::list<unsigned int> > const& pair) {
    std::list<unsigned int>	list2 = pair.second;

    std::for_each(list2.begin(), list2.end(), [&pair, &element, &count2] (unsigned int val) {
      if (pair.first == element.first && val == element.second)
	++count2;
    });
  });
  return (count2 < (count + 1));
}

std::vector<std::pair<std::string, unsigned int> >	ScoreList::top(unsigned int nb) const
{
  unsigned int						size = 0;
  unsigned int						diff = 0;
  std::vector<std::pair<std::string, unsigned int> >	top;

  std::for_each(_scores.begin(), _scores.end(), [&size] (std::pair<std::string, std::list<unsigned int> > pair) {
    size += pair.second.size();
  });

  if (size < nb)
    {
      diff = nb - size;
      nb = size;
    }
  for (unsigned int i = 0 ; i < nb ; ++i)
    {
      std::pair<std::string, unsigned int>	tmp = std::make_pair("", 0);

      std::for_each(_scores.begin(), _scores.end(), [this, &top, &tmp] (std::pair<std::string, std::list<unsigned int> > pair) {
	std::list<unsigned int>	list = pair.second;

	std::for_each(list.begin(), list.end(), [this, &top, &tmp, &pair] (unsigned int val) {
	  if (!contains(top, std::make_pair(pair.first, val)))
	    tmp = ((val >= tmp.second) ? (std::make_pair(pair.first, val)) : (tmp));
	});
      });

      top.push_back(tmp);
    }

  for (unsigned int i = 0 ; i < diff ; ++i)
    top.push_back(std::make_pair("", 0));
  return (top);
}

int	ScoreList::getBestScore(const std::string &name) const
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

std::list<unsigned int> const& ScoreList::getScore(const std::string &name) const
{
  return _scores.at(name);
}

void ScoreList::addScore(const std::string &name, unsigned int score)
{
  _scores[name].push_back(score);
}

std::list<std::string> const ScoreList::getNames() const
{
  std::list<std::string> list;

  std::for_each(_scores.cbegin(), _scores.cend(), [&] (std::pair<std::string, std::list<unsigned int> > pair) {
    list.push_back(pair.first);
  });
  return list;
}

bool ScoreList::operator==(ScoreList const& other) const
{
  return _scores == other._scores;
}

}
