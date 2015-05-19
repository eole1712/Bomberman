
#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "BasicShader.hh"
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "CameraObject.hpp"

CameraObject::CameraObject(float fov, float heigth, float width)
  :MutableObject(), _depth(1000.0f), _fov(fov), _heigth(heigth), _width(width)
{
  _projection = glm::perspective(_fov, _heigth / _width, 0.1f, _depth);

  //  _transformation = glm::lookAt(_position, _rotation, glm::vec3(0, 1, 0));
}

CameraObject::~CameraObject()
{

}

glm::mat4      	CameraObject::getProjection()
{
  return _projection;
}

glm::mat4      	CameraObject::viewTransform()
{
  return _transformation;
}

void		CameraObject::updateView()
{
  _transformation = glm::lookAt(_position, _rotation, glm::vec3(0, 1, 0));
}
