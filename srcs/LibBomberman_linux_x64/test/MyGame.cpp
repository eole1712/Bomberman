#include <list>
#include <string>
#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "MyGame.hpp"
#include "Asset3d.hpp"

#define CAMERA_HEIGTH 1000
#define CAMERA_WIDTH 1000

MyGame::MyGame()
  : _camera(90.0, CAMERA_HEIGTH, CAMERA_WIDTH),
    _speed(70)
{
  _camera.translate(glm::vec3(0.0, 4.0, 4.0));
  _camera.updateView();
}

MyGame::~MyGame()
{
  for (std::list<Asset3d *>::iterator i = _objects.begin(); i != _objects.end(); i++)
    delete (*i);
}

bool		MyGame::initialize()
{
  if (!_context.start(CAMERA_HEIGTH, CAMERA_WIDTH, "My bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  // We create a shader
  if (!_shader.load("../shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("../shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;

  // We have the bind the shader before calling the setUniform method
  _shader.bind();
  return true;
}

void		MyGame::attachObject(Asset3d *obj)
{
  _objects.push_front(obj);
}

bool		MyGame::update()
{
  float		movefactor;

  movefactor = static_cast<float>(_clock.getElapsed()) * _speed;
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;

  if (_input.getKey(SDLK_UP))
    _camera.translate(glm::vec3(0.0, 0.0, -1.0) * movefactor);
  if (_input.getKey(SDLK_DOWN))
    _camera.translate(glm::vec3(0.0, 0.0, 1.0) * movefactor);
  if (_input.getKey(SDLK_LEFT))
    _camera.translate(glm::vec3(-1.0, 0.0, 0.0) * movefactor);
  if (_input.getKey(SDLK_RIGHT))
    _camera.translate(glm::vec3(1.0, 0.0, 0.0) * movefactor);
  _camera.updateView();
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  return true;
}

void		MyGame::draw()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _shader.setUniform("view", _camera.getView());
  _shader.setUniform("projection", _camera.getProjection());
  // We draw all objects
  for (std::list<Asset3d *>::iterator i = _objects.begin(); i != _objects.end(); i++)
    (*i)->draw(_shader, _clock);
  _context.flush();
}
