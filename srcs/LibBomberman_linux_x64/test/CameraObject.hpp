
#ifndef CAMERAOBJECT_H_
# define CAMERAOBJECT_H_

# include "MutableObject.hpp"

class CameraObject : public MutableObject
{
public:
  CameraObject(float fov, float heigth, float width);
  virtual ~CameraObject();

  glm::mat4		getProjection();
  glm::mat4		viewTransform();

  void	updateView();
private:
  float			_depth;
  float			_fov;
  float			_heigth;
  float			_width;
  glm::mat4		_projection;
  glm::mat4		_transformation;
};

#endif /* !CAMERAOBJECT_H_ */
