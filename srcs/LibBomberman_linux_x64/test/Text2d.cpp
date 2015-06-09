
#include "Text2d.hpp"

#include <iostream>

Text2d::Text2d(std::string const& text, int x, int y, int width, int height, std::string const& textureName)
  : AMenuObject(x, y, width, height, textureName), _text(text)
{
  _hidden = false;

  _texture.load(textureName.c_str());
  update();
}

Text2d::~Text2d()
{
}

void		Text2d::update()
{
  _geo.clear();
  for (unsigned int i = 0; i < _text.size(); i++)
    {
      _geo.push_back(new gdl::Geometry);

      _geo[i]->pushVertex(glm::vec3(_x + i * (_width / _text.size()), _y, 0));
      _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (_width / _text.size()), _y, 0));
      _geo[i]->pushVertex(glm::vec3(_x + (i + 1) * (_width / _text.size()), _y + _height, 0));
      _geo[i]->pushVertex(glm::vec3(_x + i * (_width / _text.size()), _y + _height, 0));
      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 0.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 0.0f));
      _geo[i]->build();
    }
}

void		Text2d::listen(gdl::Input input)
{
  static bool	key_change[38] =
    {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0
    };

  const char	key[38] =
    {
      SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h,
      SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p,
      SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u, SDLK_v, SDLK_w, SDLK_x,
      SDLK_y, SDLK_z,
      SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
      SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_BACKSPACE, SDLK_SPACE
    };

  for (unsigned int i = 0; i < 38; i++)
    {
      if (input.getKey(key[i]) != key_change[i] && key_change[i] == 1)
	{
	  if (i == 36)
	    {
	      if (!_text.empty())
		_text.pop_back();
	    }
	  else
	    {
	      _text.push_back(key[i]);
	    }
	  update();
	  std::cout << "key: " << i << "text:" << _text << std::endl;
	}
      key_change[i] = input.getKey(key[i]);
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
