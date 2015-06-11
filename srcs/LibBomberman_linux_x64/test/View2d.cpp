
#include "View2d.hpp"

View2d::View2d(int x, int y, int width, int height, std::string const& textureName)
  : AMenuObject(x, y, width, height, textureName)
{
  _geo.pushVertex(glm::vec3(x, y, 0));
  _geo.pushVertex(glm::vec3(x + width, y, 0));
  _geo.pushVertex(glm::vec3(x + width, y + height, 0));
  _geo.pushVertex(glm::vec3(x, y + height, 0));

  _geo.pushUv(glm::vec2(0.0f, 1.0f));
  _geo.pushUv(glm::vec2(1.0f, 1.0f));
  _geo.pushUv(glm::vec2(1.0f, 0.0f));
  _geo.pushUv(glm::vec2(0.0f, 0.0f));

  _geo.build();
}

View2d::~View2d()
{
}

void	View2d::draw(gdl::BasicShader shader)
{
  _texture.bind();

  if (!_hidden)
    {
      _geo.draw(shader, glm::mat4(), GL_QUADS);
    }
}

void	View2d::update(gdl::Input&)
{
  ;
}
