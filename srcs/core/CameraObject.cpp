
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "CameraObject.hpp"

CameraObject::CameraObject(float fov, float height, float width)
  :Object3d(), _depth(100.0f), _fov(fov), _height(height), _width(width)
{
  _position = glm::vec3(1000, 0, 1000);
  // _height = 1000;
  // _width = 1600;
  // float tmp = _height / _width;

  _projection = glm::perspective(_fov, _height / _width, 0.1f, _depth);
}

CameraObject::~CameraObject()
{

}

glm::mat4      	CameraObject::getProjection() const
{
  return _projection;
}

glm::mat4      	CameraObject::getView() const
{
  return _view;
}

void		CameraObject::updateView()
{
  _view = glm::lookAt(_position, _rotation, glm::vec3(0, 1, 0));
}
