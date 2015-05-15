#ifndef SCORE_H_
# define SCORE_H_

#include <map>
#include <string>
#include <list>

namespace Bomberman
{
class Score
{
public:
  Score();
  virtual ~Score();
  int getBestScore(std::string const& name) const;
  std::list<unsigned int> const&  getScore(std::string const& name) const;
  void addScore(std::string const&, unsigned int);
  std::list<std::string> const getNames() const;
  bool operator==(Score const& other) const;
private:
  std::map<std::string, std::list<unsigned int> > _scores;
};

}

#endif /* !SCORE_H_ */
