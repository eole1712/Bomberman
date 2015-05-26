#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
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
    _speed(70), _player()
{
}

MyGame::~MyGame()
{
  for (std::vector<Asset3d *>::iterator i = _assets.begin(); i != _assets.end(); i++)
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
  attachObject(new Asset3d("../assets/floor.obj"));
  attachObject(new Asset3d("../assets/idst_block.obj"));
  attachObject(new Asset3d("../assets/idst_block.obj"));
  attachObject(new Asset3d("../assets/dst_block.obj"));
  attachObject(new Asset3d("../assets/fire.obj"));
  attachObject(new Asset3d("../assets/marvin.fbx"));
  _assets[PLAYER]->scale(glm::vec3(0.002));
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[PLAYER]->createSubAnim(0, "start", 0, 34);
  _assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  _assets[PLAYER]->createSubAnim(0, "end", 55, 100);
  _assets[PLAYER]->createSubAnim(0, "end2", 0, 1);
  attachObject(new Asset3d("../assets/barrel.obj"));
  _assets[BOMB]->scale(glm::vec3(0.06));
  attachObject(new Asset3d("../assets/sky.obj"));
  _assets[SKYBOX]->scale(glm::vec3(10.5 * 24));
  _assets[SKYBOX]->setPosition(glm::vec3(24 / 2, -30, 24 / 2));
  _camera.setRotation(_assets[PLAYER]->getPosition());
  _camera.setPosition(_assets[PLAYER]->getPosition() + glm::vec3(3.5, 3.5, 3));
  _camera.updateView();
  // We have the bind the shader before calling the setUniform method
  _shader.bind();
  return true;
}

void		MyGame::attachObject(Asset3d *obj)
{
  _assets.push_back(obj);
}

bool		MyGame::update()
{
  float		movefactor;
  glm::vec3	move;
  glm::vec3	newPos;
  static int	change = 0;

  movefactor = static_cast<float>(_clock.getElapsed()) * _speed;
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;

  if (_input.getKey(SDLK_UP) || _input.getKey(SDLK_DOWN))
    {
      if (change == 0)
	{
	  _assets[PLAYER]->setCurrentSubAnim("start", false);
	  _assets[PLAYER]->setCurrentSubAnim("run", true);
	}
      change = 1;
      move = (_input.getKey(SDLK_UP)) ? glm::vec3(0, 0, 0.06) : glm::vec3(0, 0, -0.06);
      move = glm::rotate(move, _assets[PLAYER]->getRotation().y,
			 glm::vec3(0, 1, 0)) * movefactor;
      newPos = _assets[PLAYER]->getPosition() + move;
      if (newPos.x < 1 || newPos.x > 24)
	newPos = glm::vec3(_assets[PLAYER]->getPosition().x, newPos.y, newPos.z);
      if (newPos.z < 1 || newPos.z > 24)
	newPos = glm::vec3(newPos.x, newPos.y, _assets[PLAYER]->getPosition().z);
      _assets[PLAYER]->setPosition(newPos);
      _camera.setRotation(newPos);
      _camera.updateView();
    }
  else if (change == 1)
    {
      change = 0;
      _assets[PLAYER]->setCurrentSubAnim("end", false);
      // _assets[PLAYER]->setCurrentSubAnim("end2", true);
    }
  if (_input.getKey(SDLK_LEFT))
    _assets[PLAYER]->rotate(glm::vec3(0, 1, 0), 3 * movefactor);
  else if (_input.getKey(SDLK_RIGHT))
    _assets[PLAYER]->rotate(glm::vec3(0, 1, 0), -3 * movefactor);
  _camera.setPosition(_assets[PLAYER]->getPosition()
		      + glm::rotate(glm::vec3(3.5, 4, 0),
				    _assets[PLAYER]->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.updateView();
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  return true;
}

void		MyGame::draw()
{
  int		i[2];

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _shader.setUniform("view", _camera.getView());
  _shader.setUniform("projection", _camera.getProjection());
  // We draw all objects
  i[0] = 0;
  while (i[0] < 25)
    {
      i[1] = 0;
      while (i[1] < 25)
	{
	  if (i[0] == 0 || i[1] == 0 || i[0] == 24 || i[1] == 24)
	    {
	      _assets[WALL]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[WALL]->draw(_shader, _clock);
	    }
	  else if (i[0] % 2 == 0 && i[1] % 2 == 0)
	    {
	      _assets[IDST_BLOCK]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[IDST_BLOCK]->draw(_shader, _clock);
	    }
	  else
	    {
	      _assets[FLOOR]->setPosition(glm::vec3(i[0], 0, i[1]));
	      _assets[FLOOR]->draw(_shader, _clock);
	    }
	  i[1]++;
	}
      i[0]++;
    }
  _assets[DST_BLOCK]->setPosition(glm::vec3(rand() % 12 * 2, 0, rand() % 12 * 2));
  _assets[DST_BLOCK]->draw(_shader, _clock);
  _assets[PLAYER]->draw(_shader, _clock);
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  _assets[SKYBOX]->scale(glm::vec3(-1));
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->scale(glm::vec3(1));
  _context.flush();
}
