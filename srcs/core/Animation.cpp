
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "Timer.hpp"
#include "Animation.hpp"
#include "Asset3d.hpp"

Animation::Animation(unsigned int const & frames, unsigned int const & speed)
  : _timer(1000000000000), _frameCount(frames), _defaultSpeed(speed)
{
}

Animation::~Animation(){}

void	Animation::setSpeed(unsigned int const speed)
{
  _defaultSpeed = speed;
}

void	Animation::setAnim(unsigned int const startframe,
			   unsigned int const endframe,
			   bool loop,
			   unsigned int const speed)
{
  Queue	anim;

  _timer.reset();
  if (startframe > _frameCount)
    anim.start = _frameCount;
  else
    anim.start = startframe;
  if (endframe > _frameCount)
    anim.end = _frameCount;
  else
    anim.end = endframe;
  if (anim.end == anim.start || speed == 0)
    return ;
  if (anim.start < anim.end)
    anim.total = anim.end - anim.start;
  else
    anim.total = anim.start - anim.end;
  anim.loop = loop;
  anim.speed = speed;
  if (!_animationQueue.empty()
      && _animationQueue.back().loop == true)
    _animationQueue.clear();
  _animationQueue.push_back(anim);
}

void	Animation::setFrameCount(unsigned int const framecount)
{
  _frameCount = framecount;
}

void	Animation::setAnim(unsigned int const startframe,
			   unsigned int const endframe,
			   bool loop)
{
  setAnim(startframe, endframe, loop, _defaultSpeed);
}

unsigned int	Animation::getFrame()
{
  uintmax_t	time;
  unsigned int	frame;
  Queue		anim;

  if (_animationQueue.empty())
    return 0;
  anim = _animationQueue.front();
  time = _timer.getElapsedTime() / anim.speed;
  while (!_animationQueue.empty() && !anim.loop && anim.total < time)
    {
      _animationQueue.pop_front();
      _timer.reset((time - anim.total) * anim.speed);
      if (!_animationQueue.empty())
	{
	  anim = _animationQueue.front();
	  time = _timer.getElapsedTime() / anim.speed;
	}
    }
  if (_animationQueue.empty())
    return 0;
  if (anim.start < anim.end)
    frame = anim.start + time % anim.total;
  else
    frame = anim.end + anim.total - (time % (anim.total));
  return frame;
}

std::string		Animation::getFrameName()
{
  std::stringstream	ss;

  ss << getFrame();
  return ss.str();
}
