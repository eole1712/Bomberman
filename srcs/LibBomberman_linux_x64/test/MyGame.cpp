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
#include "Geometry.hh"
#include "Texture.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "BasicShader.hh"
#include "OpenGL.hh"
#include "MyGame.hpp"
#include "Asset3d.hpp"
#include "View2d.hpp"
#include "Text2d.hpp"

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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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


  _assets[DST_BLOCK]->scale(glm::vec3(100));
  _assets[DST_BLOCK]->translate(glm::vec3(150, 150 , 0));
  //  _assets[DST_BLOCK]->setPosition(glm::vec3(500, 500, 0));

  _assets[PLAYER]->scale(glm::vec3(0.002));
  _assets[PLAYER]->translate(glm::vec3(3.5, 0, 3.5));
  _assets[PLAYER]->createSubAnim(0, "start", 0, 34);
  _assets[PLAYER]->createSubAnim(0, "run", 34, 55);
  _assets[PLAYER]->createSubAnim(0, "end", 55, 100);
  _assets[PLAYER]->createSubAnim(0, "end2", 0, 1);
  attachObject(new Asset3d("../assets/barrel.obj"));
  _assets[BOMB]->scale(glm::vec3(0.06));
  attachObject(new Asset3d("../assets/sky.obj"));
  _assets[SKYBOX]->scale(glm::vec3(10.5 * 10));
  _camera.setRotation(_assets[PLAYER]->getPosition());
  _camera.setPosition(_assets[PLAYER]->getPosition() + glm::vec3(3.5, 3.5, 3));
  _camera.updateView();
  // We have the bind the shader before calling the setUniform method
  _text = new Text2d("test", 150, 500, 700, 100, "../assets/textures/alpha3.tga");
  _shader.bind();
  _text = new Text2d("15 PONEYROSE petit test", 150, 0, 700, 100, "../assets/textures/alpha3Blue.tga");
  _text2 = new Text2d("25 PONEYBleus petit test", 150, 100, 800, 100, "../assets/textures/alpha3Blue.tga");
  // _grid.addObject(_text, [] () {
  //   std::cout << "Pink Pony" << std::endl;
  // });
  // _grid.addObject(_text2, [] () {
  //   std::cout << "Blue Pony" << std::endl;
  // });
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
		      + glm::rotate(glm::vec3(3.5, 1.5, 0),
				    _assets[PLAYER]->getRotation().y + 90,
				    glm::vec3(0, 1, 0)));
  _camera.updateView();
  _text->listen(_input);
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


  //_shader.setUniform("playercolor", _);
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
  // _assets[DST_BLOCK]->setPosition(glm::vec3(rand() % 12 * 2, 0, rand() % 12 * 2));
  // _assets[DST_BLOCK]->draw(_shader, _clock);
  _assets[PLAYER]->draw(_shader, _clock);
  _assets[SKYBOX]->draw(_shader, _clock);
  //<<<<<<< Updated upstream
  _assets[SKYBOX]->rotate(glm::vec3(0, 1, 0), 180);
  _assets[SKYBOX]->scale(glm::vec3(-1));
  _assets[SKYBOX]->draw(_shader, _clock);
  _assets[SKYBOX]->scale(glm::vec3(1));

  // 2D TESTS
  glDisable(GL_DEPTH_TEST);

  _shader.setUniform("view", glm::mat4());
  _shader.setUniform("projection", glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, -1000.0f, 1000.0f));

  // Text2d	text("15 PONEYROSE petit test", 150, 0, 700, 100, "../assets/textures/alpha2.tga");
  // Text2d	text2("25 PONEYBleus petit test", 150, 100, 800, 100, "../assets/textures/alpha2.tga");
  View2d	lol(400, 600, 200, 200, std::string("../assets/textures/lol.tga"));
  View2d	lol2(450, 600, 200, 200, std::string("../assets/textures/lol.tga"));

  // if (_input.getKey(SDLK_s))
  //   _grid.moveRight();
  // if (_input.getKey(SDLK_z))
  //   _grid.moveLeft();
  // if (_input.getKey(SDLK_TAB))
  //   _grid.actionOnFocus();

  // _grid.drawGrid(_shader);

  //text.draw(_shader);
  lol.draw(_shader);
  lol2.draw(_shader);
  //lol.draw(_shader);

  _text->draw(_shader);

  //3D interface

  //  _shader.setUniform("view", glm::mat4());
  // _shader.setUniform("projection",  glm::perspective(60.0f, (float)1000 / (float)1000, 0.1f, 100.0f));

  _assets[DST_BLOCK]->rotate(glm::vec3(0, 1 ,0), 1);
  _assets[DST_BLOCK]->draw(_shader, _clock);

  glEnable(GL_DEPTH_TEST);
  _context.flush();
}
