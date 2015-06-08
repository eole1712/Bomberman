
#include "Text2d.hpp"

Text2d::Text2d(std::string const& text, int x, int y, int width, int height, std::string const& textureName)
  : AMenuObject(x, y, width, height, textureName), _text(text)
{
  for (unsigned int i = 0; i < text.size(); i++)
    {
      _geo.push_back(new gdl::Geometry);

      _geo[i]->pushVertex(glm::vec3(x + i * (width / text.size()), y, 0));
      _geo[i]->pushVertex(glm::vec3(x + (i + 1) * (width / text.size()), y, 0));
      _geo[i]->pushVertex(glm::vec3(x + (i + 1) * (width / text.size()), y + height, 0));
      _geo[i]->pushVertex(glm::vec3(x + i * (width / text.size()), y + height, 0));


      // _geo[i]->pushUv(glm::vec2(0.0f, 1.0f));
      // _geo[i]->pushUv(glm::vec2(1.0f, 1.0f));
      // _geo[i]->pushUv(glm::vec2(1.0f, 0.0f));
      // _geo[i]->pushUv(glm::vec2(0.0f, 0.0f));

      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 1.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * (_text.at(i) + 1), 0.0f));
      _geo[i]->pushUv(glm::vec2(0.0078125 * _text.at(i), 0.0f));

      _geo[i]->build();
    }
}

Text2d::~Text2d()
{
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
