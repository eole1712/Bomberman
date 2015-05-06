#include <unistd.h>
#include "Timer.hpp"

namespace PlazzaTime
{

Timer::Timer(uintmax_t time)
  :_time(std::chrono::microseconds(35000)),
   _saveTime(0),
   _clock(std::chrono::system_clock::now())
{

}

Timer::~Timer()
{}

void	Timer::start()
{
  _clock = std::chrono::system_clock::now();
}

void	Timer::stop()
{
  _saveTime = getCurTime();
}



void	Timer::reset()
{
  _clock = std::chrono::system_clock::now();
  _saveTime = std::chrono::microseconds(0);
}

bool	Timer::isFinished()
{
  usleep(1);
  return (this->getCurTime() > _time);
}

uintmax_t			Timer::getElapsedTime()
{
  usleep(1);
  return (getCurTime().count());
}

std::chrono::microseconds	Timer::getCurTime()
{
  std::chrono::time_point<std::chrono::system_clock> newTime = std::chrono::system_clock::now();
  return (_saveTime + std::chrono::duration_cast<std::chrono::microseconds>((newTime - _clock)));
}

}
