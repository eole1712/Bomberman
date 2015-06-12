
#include "Text2d.hpp"

#include <iostream>

Text2d::Text2d(std::string const& text, int x, int y, int width, int height, std::string const& textureName)
  : AMenuObject(x, y, width, height, textureName), _modif(false), _text(text), _size((1.0f / 40.0f) * height)
{
  _hidden = false;

  if (!_texture.load(textureName.c_str()))
    std::cout << "failed to load " << textureName << std::endl;;
  update();
}

Text2d::Text2d(std::string const& text, int x, int y, int width, int height, std::string const& textureName, int size)
  : AMenuObject(x, y, width, height, textureName), _modif(false), _text(text), _size(size)
{
  _hidden = false;

  if (!_texture.load(textureName.c_str()))
    std::cout << "failed to load " << textureName << std::endl;;
  update();
}

Text2d::~Text2d()
{
}

void		Text2d::update()
{
  _geo.clear();
  for (unsigned int i = 0; i < _text.size() && (34.98 * _size * i) < _width + _size * i
	 ; i++)
    {
      _geo.push_back(new gdl::Geometry);

      _geo[i]->pushVertex(glm::vec3(_x + i * (34.98 * _size),
				    _y,
				    0));
      _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (34.98 * _size),
				    _y,
				    0));
      _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (34.98 * _size),
				    _y + 40 * _size,
				    0));
      _geo[i]->pushVertex(glm::vec3(_x + i * (34.98 * _size),
				    _y + 40 * _size,
				    0));

      // _geo[i]->pushVertex(glm::vec3(_x + i * (34.98 * _size), _y, 0));
      // _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (34.98 * _size),
      // _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (34.98 * _size),
      // _geo[i]->pushVertex(glm::vec3(_x + i * (34.98 * _size), _y + 40 * _size, 0));

      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 0.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 0.0f));
      _geo[i]->build();
    }
}

void		Text2d::listen(gdl::Input input)
{
  char		key;
  static bool	key_change[64] =
    {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0
    };

  for (unsigned int i = 0; i < 64; i++)
    {
      if (i < 26)
	key = 'a' + i;
      else if (i < 52)
	key = 'A' + i - 26;
      else if (i < 62)
	key = '0' + i - 52;
      else if (i < 63)
	key = ' ';
      else
	key = SDLK_BACKSPACE;
      if (input.getKey(key) != key_change[i] && key_change[i] == 1)
	{
	  if (i == 63)
	    {
	      if (!_text.empty())
		_text.pop_back();
	    }
	  else
	    _text.push_back(key);
	  update();
	}
      key_change[i] = input.getKey(key);
    }
}

void	Text2d::setHidden(bool hidden)
{
  _hidden = hidden;
}

void	Text2d::draw(gdl::BasicShader shader)
{
  _texture.bind();

  std::vector<gdl::Geometry*>::iterator	it;

  if (!_hidden)
    {
      for (it = _geo.begin(); it != _geo.end(); it++)
	{
	  (*it)->draw(shader, glm::mat4(), GL_QUADS);
	}
    }
}

void	Text2d::setModifiable()
{
  _modif = true;
}

bool	Text2d::isModifiable() const
{
  return _modif;
}

void	Text2d::update(gdl::Input &in)
{
  if (_modif)
    listen(in);
}

std::string const&	Text2d::getText() const
{
  return _text;
}
