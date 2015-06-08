#ifndef SCORELIST_H_
# define SCORELIST_H_

# include <map>
# include <string>
# include <list>

namespace Bomberman
{
class		ScoreList
{
public:
  ScoreList();
  virtual ~ScoreList();
  int					getBestScore(std::string const& name) const;
  std::list<unsigned int> const&	getScore(std::string const& name) const;
  void					addScore(std::string const&, unsigned int);
  std::list<std::string> const		getNames() const;
  bool					operator==(ScoreList const& other) const;
private:
  std::map<std::string, std::list<unsigned int> >	_scores;
};

}

#endif /* !SCORELIST_H_ */
