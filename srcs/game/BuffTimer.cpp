#include "BuffTimer.hpp"

Bomberman::BuffTimer::BuffTimer(IBuff *buff)
  : Timer(buff->getDuration() * 1000000), _buff(buff)
{

}

Bomberman::BuffTimer::BuffTimer(IBuff *buff, unsigned int time)
  : Timer(buff->getDuration() * 1000000 - time), _buff(buff)
{

}

Bomberman::BuffTimer::~BuffTimer()
{

}

Bomberman::IBuff const*	Bomberman::BuffTimer::getBuff() const
{
  return _buff;
}
