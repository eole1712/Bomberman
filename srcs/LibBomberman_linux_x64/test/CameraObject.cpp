
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "CameraObject.hpp"

CameraObject::CameraObject(float fov, float heigth, float width)
  :Object3d(), _depth(1000.0f), _fov(fov), _heigth(heigth), _width(width)
{
  _projection = glm::perspective(_fov, _heigth / _width, 0.1f, _depth);
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