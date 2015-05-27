
#ifndef CAMERAOBJECT_H_
# define CAMERAOBJECT_H_

# include "Object3d.hpp"

class CameraObject : public Object3d
{
public:
  CameraObject(float fov, float heigth, float width);
  virtual ~CameraObject();

  glm::mat4		getProjection() const;
  glm::mat4		getView() const;

  void			updateView();
public:
  float			_depth;
  float			_fov;
  float			_height;
  float			_width;
  glm::mat4		_projection;
  glm::mat4		_view;
};

#endif /* !CAMERAOBJECT_H_ */
