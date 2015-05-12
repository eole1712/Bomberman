#ifndef __SMARTFACTORY_HPP__
# define __SMARTFACTORY_HPP__

# include <string>
# include "IClonable.hpp"

/*
** SmartFactory
** Singleton design pattern
** Factory that can learn/unlearn types and then generates them
** Be careful, Type has to be able to use the clone member function /!\
*/
template <typename Type = IClonable>
class SmartFactory
{
public:
  typedef std::map<std::string, Type*>	SmartBook;
  typedef std::pair<std::string, Type*>	SmartEntry;

private:
  SmartFactory()
  {
  }

  ~SmartFactory()
  {    
    for (SmartBook::iterator it = _book.begin() ;
         it != _book.end() ;
         ++it)
      {
        if (it->second != NULL)
          delete (it->second);
      }
  }

public:
  static SmartFactory*	getInstance()
  {
    if (_instance == NULL)
      _instance = new SmartFactory();
    return (_instance);
  }

  static void		destroy()
  {
    if (_instance == NULL)
      return ;
    delete (_instance);
    _instance = NULL;
  }

public:
  bool			learn(Type const* type)
  {
    std::pair<SmartBook::iterator, bool>	ret;

    if (type == NULL)
      return (false);
    ret = _book.insert(SmartEntry(type->getName(), type->clone()));
    return (ret.second);
  }

  bool			unlearn(std::string const& name)
  {
    if (_book.erase(name) == 0)
      return (false);
    return (true);
  }

  Type*			generate(std::string const& name) const
  {
    SmartBook::const_iterator      it;

    if ((it = _book.find(name)) == _book.end())
      return (NULL);
    return (it->second->clone());
  }

protected:
  SmartBook              _book;
  static SmartFactory*   _instance;
};

#endif /* !__SMARTFACTORY_HPP__ */
