//
// GenericMap.hpp for nibbler in /home/tea_a/Work/cpp_nibbler/sources/lib_sfml
//
// Made by Alexandre Tea
// Login   <tea_a@epitech.net>
//
// Started on  Tue Mar 24 22:53:02 2015 Alexandre Tea
// Last update Sat Apr  4 00:00:09 2015 Alexandre Tea
//

#ifndef __GENERICMAP_HPP__
# define __GENERICMAP_HPP__

# include <cstdlib>
# include <stdexcept>
# include "StringConversion.hpp"

template <typename T>
class GenericMap
{
public:
  GenericMap() : _map(NULL), _width(0), _height(0)
  {
  }

  GenericMap(const unsigned int width,
      const unsigned int height) :
    _map(NULL), _width(width), _height(height)
  {
    _map = new T[width * height];
  }

  GenericMap(const unsigned int width,
      const unsigned int height, T* map) :
    _map(map), _width(width), _height(height)
  {
  }

  ~GenericMap()
  {
    if (_map != NULL)
      delete[] (_map);
  }

public:
  GenericMap(GenericMap<T> const& other)
  {
    copy(other);
  }

  GenericMap<T>&	operator=(GenericMap<T> const& other)
  {
    copy(other);
    return (*this);
  }

public:
  void			setMap(const unsigned int width,
			       const unsigned int height, T* map)
  {
    _width = width;
    _height = height;
    if (_map != NULL)
      delete[] (_map);
    _map = map;
  }

  void			copy(GenericMap const& other)
  {
    _width = other._width;
    _height = other._height;
    if (_map != NULL)
      delete[] (_map);
    _map = new T[_width * _height];
  }

  void			setCellValue(const unsigned int x,
				     const unsigned int y,
				     const T value)
  {
    if (x > _width - 1 || y > _height - 1)
      throw std::out_of_range("Coordinates (" +
			      Conversion::typeToString<unsigned int>(x) + "," +
			      Conversion::typeToString<unsigned int>(y) +
			      ") are out of range.");
    _map[(y * _width) + x] = value;
  }

public:
  T			getCellValue(const unsigned int x,
				     const unsigned int y) const
  {
    return (_map[(y * _width) + x]);
  }

  unsigned int		getWidth() const
  {
    return (_width);
  }

  unsigned int		getHeight() const
  {
    return (_height);
  }

protected:
  T*		_map;
  unsigned int	_width;
  unsigned int	_height;
};

#endif /* !__GENERICMAP_HPP__ */
