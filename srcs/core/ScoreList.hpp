#ifndef SCORELIST_H_
# define SCORELIST_H_

# include <map>
# include <string>
# include <list>
# include <vector>

namespace Bomberman
{
class		ScoreList
{
public:
  ScoreList();
  virtual ~ScoreList();
  bool					contains(std::vector<std::pair<std::string,
						 unsigned int> > const&,
						 std::pair<std::string, unsigned int> const&) const;
  std::vector<std::pair<std::string, unsigned int> >	top(unsigned int) const;
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
